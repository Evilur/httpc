#include "http.h"
#include "error.h"

#include <stdio.h>
#include <string.h>

int32_t http_handle_request(char* buffer, int32_t size) {
    return *buffer + size;
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

http_request_method_t http_get_request_method(
    const http_request_headers_t* const request_headers
) {
    return request_headers->flags & HTTP_METHOD_MASK;
}

void http_set_request_method(
    http_request_headers_t* const request_headers,
    const http_request_method_t request_method
) {
    request_headers->flags =
        (request_headers->flags & ~HTTP_METHOD_MASK) |
        (request_method & HTTP_METHOD_MASK);
}

http_transfer_encoding_t http_get_transfer_encoding(
    const http_request_headers_t* const request_headers
) {
    return request_headers->flags & HTTP_TRANSFER_ENCODING_MASK;
}

void http_set_transfer_encoding(
    http_request_headers_t* const request_headers,
    const http_transfer_encoding_t transfer_encoding
) {
    request_headers->flags =
        (request_headers->flags & ~HTTP_TRANSFER_ENCODING_MASK) |
        (transfer_encoding & HTTP_TRANSFER_ENCODING_MASK);
}

http_content_encoding_t http_get_content_encoding(
    const http_request_headers_t* const request_headers
) {
    return request_headers->flags & HTTP_CONTENT_ENCODING_MASK;
}

void http_set_content_encoding(
    http_request_headers_t* const request_headers,
    const http_content_encoding_t content_encoding
) {
    request_headers->flags =
        (request_headers->flags & ~HTTP_CONTENT_ENCODING_MASK) |
        (content_encoding & HTTP_CONTENT_ENCODING_MASK);
}

http_connection_type_t http_get_connection_type(
    const http_request_headers_t* const request_headers
) {
    return request_headers->flags & HTTP_CONNECTION_MASK;
}

void http_set_connection_type(
    http_request_headers_t* const request_headers,
    const http_connection_type_t connection_type
) {
    request_headers->flags =
        (request_headers->flags & ~HTTP_CONNECTION_MASK) |
        (connection_type & HTTP_CONNECTION_MASK);
}

bool_t http_is_client_support_encoding(
    const http_request_headers_t* const request_headers,
    const http_accept_encoding_t accept_encoding
) {
    return (request_headers->flags & accept_encoding) != 0;
}

void http_set_client_supported_encoding(
    http_request_headers_t* const request_headers,
    const http_accept_encoding_t accept_encoding,
    const bool_t value
) {
    if (value)
        request_headers->flags |= accept_encoding;
    else
        request_headers->flags &= ~accept_encoding;
}

void http_reset_client_supported_encoding(
    http_request_headers_t* const request_headers
) {
    request_headers->flags &= ~HTTP_ACCEPT_ENCODING_MASK;
}
