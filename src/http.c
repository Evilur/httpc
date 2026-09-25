#include "../properties.h"
#include "http.h"
#include "ctrie.h"
#include "error.h"
#include "null.h"
#include "util.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ctrie_t http_supported_methods_ctrie;
ctrie_t http_supported_headers_ctrie;
ctrie_t http_supported_encoding_ctrie;

int32_t http_init(void) {
    /* Set supported methods */
    ctrie_key_value_t supported_methods[] = {
        { "GET",     { HTTP_METHOD_GET } },
        { "HEAD",    { HTTP_METHOD_HEAD } },
        { "POST",    { HTTP_METHOD_POST } },
    };
    const int32_t supported_methods_size =
        sizeof(supported_methods) / sizeof(ctrie_key_value_t);

    /* Set supported headers */
    ctrie_key_value_t supported_headers[] = {
        { "Content-Length",    { HTTP_SUPPORTED_HEADER_CONTENT_LENGTH } },
        { "Connection",        { HTTP_SUPPORTED_HEADER_CONNECTION } },
        { "Accept-Encoding",   { HTTP_SUPPORTED_HEADER_ACCEPT_ENCODING } },
        { "Transfer-Encoding", { HTTP_SUPPORTED_HEADER_TRANSFER_ENCODING } },
        { "Expect",            { HTTP_SUPPORTED_HEADER_EXPECT } },
        { "Range",             { HTTP_SUPPORTED_HEADER_RANGE } },
    };
    const int32_t supported_headers_size =
        sizeof(supported_headers) / sizeof(ctrie_key_value_t);

    /* Set supported encoding */
    ctrie_key_value_t supported_encoding[] = {
        { "zstd", { HTTP_ACCEPT_ENCODING_ZSTD } },
        { "br",   { HTTP_ACCEPT_ENCODING_BR } },
        { "gzip", { HTTP_ACCEPT_ENCODING_GZIP } }
    };
    const int32_t supported_encoding_size =
        sizeof(supported_encoding) / sizeof(ctrie_key_value_t);

    /* Create ctries and return the code on error */
    if (ctrie_create(&http_supported_headers_ctrie,
                     supported_headers,
                     supported_headers_size) == -1 ||
        ctrie_create(&http_supported_methods_ctrie,
                     supported_methods,
                     supported_methods_size) == -1 ||
        ctrie_create(&http_supported_encoding_ctrie,
                     supported_encoding,
                     supported_encoding_size) == -1)
        return -1;

    /* Return the success code */
    return 0;
}

int32_t http_handle_request_uri(http_request_headers_t* const request_headers,
                                const socket_fd_t socket_fd,
                                char** const buffer_ptr,
                                int32_t* const buffer_size) {
    /* Save a const buffer pointer and a size */
    char* const buffer = *buffer_ptr;
    const int32_t buffer_origin_size = *buffer_size;

    /* Try to get the new line sequence */
    char* const end_of_line =
        util_memmem(buffer, buffer_origin_size, "\r\n", 2);

    /* If there is not a full string in the buffer */
    if (end_of_line == null) {
        /* If the buffer is full already */
        if (*buffer_size >= MAX_BUFFER_SIZE) {
            http_send_default_response(
                socket_fd, buffer, buffer_origin_size,
                414, "URI Too Long"
            );
            return -1;
        }

        /* If the buffer still writable */
        return 1;
    }

    /* If there is a uri string in the buffer,
     * Try to get the request method */
    const ctrie_data_t* const method_ptr =
        ctrie_get(&http_supported_methods_ctrie, buffer_ptr, ' ');
    if (method_ptr == null) {
        http_send_default_response(socket_fd, buffer, *buffer_size,
                                   501, "Not Implemented");
        return -1;
    }

    /* Unescape the uri in-place */
    char *source_ptr = *buffer_ptr;
    char *dest_ptr = *buffer_ptr;
    while (*source_ptr != '\0' && *source_ptr != ' ' && *source_ptr != '\r') {
        if (*source_ptr == '%') {
            /* Get hex values */
            const int high = util_hexval((unsigned char)*++source_ptr);
            const int low = util_hexval((unsigned char)*++source_ptr);

            /* If there is an invalid uri */
            if (high == -1 || low == -1) {
                http_send_default_response(socket_fd, buffer,
                                           buffer_origin_size,
                                           400, "Bad Request");
                return -1;
            }

            /* Write the data and update the pointers */
            *dest_ptr = (char)((high << 4) | low);
            ++dest_ptr;
            ++source_ptr;
        } else {
            /* Write the data and update the pointers */
            *dest_ptr = *source_ptr;
            ++dest_ptr;
            ++source_ptr;
        }
    }

    /* Set the uri terminate character */
    *dest_ptr = '\0';

    /* Copy the uri */
    const uint64_t uri_length = (uint64_t)(dest_ptr - *buffer_ptr);
    request_headers->uri = malloc(uri_length + 1);
    memcpy(request_headers->uri, *buffer_ptr, uri_length);
    request_headers->uri[uri_length] = '\0';

    /* Update the buffer size and the pointer to handle headers next */
    *buffer_ptr = end_of_line + 2;
    *buffer_size -= (int32_t)(*buffer_ptr - buffer);

    /* Return the success code */
    return 0;
}

int32_t http_handle_request_headers(
    http_request_headers_t* const request_headers,
    const socket_fd_t socket_fd,
    char** const buffer_ptr,
    int32_t* const buffer_size
) {
    /* Save a const buffer pointer and a size */
    char* const buffer = *buffer_ptr;
    const int32_t buffer_origin_size = *buffer_size;

    /* Get the end of a buffer */
    const char* const buffer_end = buffer + buffer_origin_size;

    /* While there is not a '\r\n\r\n' sequence */
    do {
        /* Try to find the next end of line sequence */
        char* const end_of_line =
            util_memmem(*buffer_ptr, *buffer_size, "\r\n", 2);

        /* If there is not a full string in the buffer */
        if (end_of_line == null) {
            /* If the buffer is full already */
            if (*buffer_size >= MAX_BUFFER_SIZE) {
                http_send_default_response(
                    socket_fd, buffer, buffer_origin_size,
                    431, "Request Header Fields Too Large"
                );
                return -1;
            }

            /* If the buffer still writable */
            return 1;
        } else *end_of_line = '\0';

        /* Try to find the header name in the ctrie of the supported */
        const ctrie_data_t* const header_name =
            ctrie_get(&http_supported_headers_ctrie, buffer_ptr, ':');

        /* If the header in the list of the supported */
        if (header_name != null) {
            *buffer_ptr = util_trim(*buffer_ptr + 1);
            switch (header_name->int32) {
                case HTTP_SUPPORTED_HEADER_ACCEPT_ENCODING:
                    while (*buffer_ptr < end_of_line) {
                        /* Try to get the end of the current algo name */
                        char* const end_of_algo_name =
                            strpbrk(*buffer_ptr, ",; ");
                        if (end_of_algo_name == null) break;

                        /* Save the old terminate char and make it \0 */
                        const char old_end = *end_of_algo_name;
                        *end_of_algo_name = '\0';

                        /* Add the supported compression type */
                        const ctrie_data_t* compression_type =
                            ctrie_get(&http_supported_encoding_ctrie,
                                      buffer_ptr, '\0');
                        if (compression_type != null)
                            http_set_client_supported_encoding(
                                request_headers,
                                (http_accept_encoding_t)
                                compression_type->int32,
                                1
                            );
                        if (compression_type != null)
                            printf("%d\n", compression_type->int32);

                        /* Go to the next algo name */
                        switch (old_end) {
                            case ',':
                                *buffer_ptr = util_trim(end_of_algo_name + 1);
                                break;
                            case ';':
                                *buffer_ptr = strchr(end_of_algo_name, ',');
                                if (*buffer_ptr == null)
                                    goto end_of_accept_encoding;
                                else *buffer_ptr = util_trim(*buffer_ptr + 1);
                                break;
                            default:
                                goto end_of_accept_encoding;
                        }
                    }
                end_of_accept_encoding:
                    break;

                case HTTP_SUPPORTED_HEADER_CONNECTION:
                    http_set_connection_type(
                        request_headers,
                        util_strcicmp(*buffer_ptr, "keep-alive") ?
                        HTTP_CONNECTION_KEEPALIVE :
                        HTTP_CONNECTION_CLOSE);
                    break;

                case HTTP_SUPPORTED_HEADER_CONTENT_LENGTH:
                    if (*buffer != '0')
                        http_send_default_response(
                            socket_fd, buffer, buffer_origin_size,
                            400, "Bad Request");
                    return -1;

                case HTTP_SUPPORTED_HEADER_EXPECT:
                    http_send_default_response(
                        socket_fd, buffer, buffer_origin_size,
                        417, "Expectation Failed");
                    return -1;

                case HTTP_SUPPORTED_HEADER_RANGE:
                    if (end_of_line < *buffer_ptr) break;
                    {
                        const uint64_t range_str_length =
                            (uint64_t)(end_of_line - *buffer_ptr);
                        request_headers->range = malloc(range_str_length + 1);
                        if (request_headers->range == null) break;
                        memcpy(request_headers->range, *buffer_ptr,
                               range_str_length);
                        request_headers->range[range_str_length] = '\0';
                    }
                    break;

                case HTTP_SUPPORTED_HEADER_TRANSFER_ENCODING:
                    http_send_default_response(
                        socket_fd, buffer, buffer_origin_size,
                        501, "Not Implemented");
                    return -1;
            }
        }

        /* Update the buffer pointer and the size */
        *buffer_ptr = end_of_line + 2;
        *buffer_size = (int32_t)(buffer_end - *buffer_ptr);
    } while (memcmp(*buffer_ptr, "\r\n", 2) != 0);

    /* Return success code */
    return 0;
}

int32_t http_send_default_response(const socket_fd_t socket_fd,
                                   char* const buffer, int32_t buffer_size,
                                   const int32_t status_code,
                                   const char* status_description) {
    /* Default response */
    static const char response_headers[] =
        "HTTP/1.1 %d %s\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "\r\n";
    static const char response_body[] =
        "<!DOCTYPE html><html>"
        "<head><title>%d %s</title></head>"
        "<body><h1 style='text-align:center'>%d %s</h1><hr></body>"
        "</html>";

    /* Calculate the body size */
    const int32_t calced_body_size = (int32_t)sizeof(response_body)
        -1                                          // \0 char
        -4 * 2                                      // %d %s (twice)
        +3 * 2                                      // status code (twice)
        + (int32_t)strlen(status_description) * 2;  // Description (twice)

    /* Pointer to the buffer with offset */
    char* buffer_ptr = buffer;

    /* Write the headers to the buffer */
    const int32_t headers_size = snprintf(buffer_ptr, (uint64_t)buffer_size,
                                          response_headers,
                                          status_code, status_description,
                                          calced_body_size);
    if (headers_size >= buffer_size ||
        headers_size < 0) {
        printerr("Failed to send the default response:\n"
                 "Buffer is too small");
        return -1;
    }
    buffer_ptr += headers_size;
    buffer_size -= headers_size;

    /* Write the body to the buffer */
    const int32_t body_size = snprintf(buffer_ptr, (uint64_t)buffer_size,
                                       response_body,
                                       status_code, status_description,
                                       status_code, status_description);
    if (body_size >= buffer_size ||
        body_size < 0) {
        printerr("Failed to send the default response:\n"
                 "Buffer is too small");
        return -1;
    }

    /* Check if out body size calulations were right */
    if (body_size != calced_body_size) {
        printerr("Failed to calculate the body size");
        return -1;
    }

    /* Write the response to the buffer */
    socket_write(socket_fd, buffer, headers_size + body_size);

    /* Return the success code */
    return 0;
}

http_connection_type_t http_get_connection_type(
    const http_request_headers_t* const request_headers
) {
    return request_headers->flags & (uint8_t)HTTP_CONNECTION_MASK;
}

void http_set_connection_type(
    http_request_headers_t* const request_headers,
    const http_connection_type_t connection_type
) {
    request_headers->flags =
        (request_headers->flags & (uint8_t)~HTTP_CONNECTION_MASK) |
        (connection_type & HTTP_CONNECTION_MASK);
}

bool_t http_is_client_support_encoding(
    const http_request_headers_t* const request_headers,
    const http_accept_encoding_t accept_encoding
) {
    return (request_headers->flags & (uint8_t)accept_encoding) != 0;
}

void http_set_client_supported_encoding(
    http_request_headers_t* const request_headers,
    const http_accept_encoding_t accept_encoding,
    const bool_t value
) {
    if (value)
        request_headers->flags |= (uint8_t)accept_encoding;
    else
        request_headers->flags &= (uint8_t)~accept_encoding;
}

void http_reset_client_supported_encoding(
    http_request_headers_t* const request_headers
) {
    request_headers->flags &= (uint8_t)~HTTP_ACCEPT_ENCODING_MASK;
}
