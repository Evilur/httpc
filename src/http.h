#ifndef HTTP_H
#define HTTP_H

#include "bool.h"
#include "socket.h"

#include <stdint.h>

#define HTTP_METHOD_SHIFT             (uint16_t)0x0u
#define HTTP_TRANSFER_ENCODING_SHIFT  (uint16_t)0x3u
#define HTTP_CONTENT_ENCODING_SHIFT   (uint16_t)0x4u
#define HTTP_ACCEPT_ENCODING_SHIFT    (uint16_t)0x6u
#define HTTP_CONNECTION_SHIFT         (uint16_t)0x9u

#define HTTP_METHOD_MASK                                                       \
    (uint16_t)(0x7u << HTTP_METHOD_SHIFT)
#define HTTP_TRANSFER_ENCODING_MASK                                            \
    (uint16_t)(0x1u << HTTP_TRANSFER_ENCODING_SHIFT)
#define HTTP_CONTENT_ENCODING_MASK                                             \
    (uint16_t)(0x3u << HTTP_CONTENT_ENCODING_SHIFT)
#define HTTP_ACCEPT_ENCODING_MASK                                              \
    (uint16_t)(0x7u << HTTP_ACCEPT_ENCODING_SHIFT)
#define HTTP_CONNECTION_MASK                                                   \
    (uint16_t)(0x1u << HTTP_CONNECTION_SHIFT)

typedef enum http_request_method {
    HTTP_METHOD_NONE    = 0x0u << HTTP_METHOD_SHIFT,
    HTTP_METHOD_GET     = 0x1u << HTTP_METHOD_SHIFT,
    HTTP_METHOD_HEAD    = 0x2u << HTTP_METHOD_SHIFT,
    HTTP_METHOD_POST    = 0x3u << HTTP_METHOD_SHIFT,
    HTTP_METHOD_PUT     = 0x4u << HTTP_METHOD_SHIFT,
    HTTP_METHOD_PATCH   = 0x5u << HTTP_METHOD_SHIFT,
    HTTP_METHOD_DELETE  = 0x6u << HTTP_METHOD_SHIFT,
    HTTP_METHOD_OPTIONS = 0x7u << HTTP_METHOD_SHIFT
} http_request_method_t;

typedef enum http_transfer_encoding {
    HTTP_TRANSFER_ENCODING_NONE    = 0x0u << HTTP_TRANSFER_ENCODING_SHIFT,
    HTTP_TRANSFER_ENCODING_CHUNKED = 0x1u << HTTP_TRANSFER_ENCODING_SHIFT
} http_transfer_encoding_t;

typedef enum http_content_encoding {
    HTTP_CONTENT_ENCODING_NONE    = 0x0u << HTTP_CONTENT_ENCODING_SHIFT,
    HTTP_CONTENT_ENCODING_ZSTD    = 0x1u << HTTP_CONTENT_ENCODING_SHIFT,
    HTTP_CONTENT_ENCODING_BR      = 0x2u << HTTP_CONTENT_ENCODING_SHIFT,
    HTTP_CONTENT_ENCODING_GZIP    = 0x3u << HTTP_CONTENT_ENCODING_SHIFT
} http_content_encoding_t;

typedef enum http_accept_encoding {
    HTTP_ACCEPT_ENCODING_ZSTD = 0x1u << (HTTP_ACCEPT_ENCODING_SHIFT + 0x0u),
    HTTP_ACCEPT_ENCODING_BR   = 0x1u << (HTTP_ACCEPT_ENCODING_SHIFT + 0x1u),
    HTTP_ACCEPT_ENCODING_GZIP = 0x1u << (HTTP_ACCEPT_ENCODING_SHIFT + 0x2u)
} http_accept_encoding_t;

typedef enum http_connection_type {
    HTTP_CONNECTION_CLOSE     = 0x0u << HTTP_CONNECTION_SHIFT,
    HTTP_CONNECTION_KEEPALIVE = 0x1u << HTTP_CONNECTION_SHIFT
} http_connection_type_t;

typedef enum http_connection_state {
    HTTP_CONNECTION_READING_URI,
    HTTP_CONNECTION_READING_HEADERS,
    HTTP_CONNECTION_READING_BODY,
    HTTP_CONNECTION_SENDING_RESPONSE
} http_connection_state_t;

/**
 * Request headers struct
 */
typedef struct http_request_headers {
    char* uri;
    uint64_t content_length;
    char* range;

    /**
     * 3bits: http method (GET|POST|etc.)
     * 1bit:  Transfer-Encoding (none/chunked)
     * 2bits: Content-Encoding (none|zstd|br|gzip)
     * 3bits: Accept-Encoding (gzip, br, zstd)
     * 1bit:  Connection (keep-alive|close)
     */
    uint16_t flags;
} http_request_headers_t;

int32_t http_handle_uri(http_request_headers_t* request_headers,
                        socket_fd_t socket_fd,
                        char* const* buffer_ptr, int32_t* buffer_size);

int32_t http_send_default_response(socket_fd_t socket_fd,
                                   char* buffer, int32_t buffer_size,
                                   int32_t status_code,
                                   const char* status_description);

http_request_method_t http_get_request_method(
    const http_request_headers_t* request_headers
);

void http_set_request_method(
    http_request_headers_t* request_headers,
    http_request_method_t request_method
);

http_transfer_encoding_t http_get_transfer_encoding(
    const http_request_headers_t* request_headers
);

void http_set_transfer_encoding(
    http_request_headers_t* request_headers,
    http_transfer_encoding_t transfer_encoding
);

http_content_encoding_t http_get_content_encoding(
    const http_request_headers_t* request_headers
);

void http_set_content_encoding(
    http_request_headers_t* request_headers,
    http_content_encoding_t content_encoding
);

http_connection_type_t http_get_connection_type(
    const http_request_headers_t* request_headers
);

void http_set_connection_type(
    http_request_headers_t* request_headers,
    http_connection_type_t connection_type
);

bool_t http_is_client_support_encoding(
    const http_request_headers_t* request_headers,
    http_accept_encoding_t accept_encoding
);

void http_set_client_supported_encoding(
    http_request_headers_t* request_headers,
    http_accept_encoding_t accept_encoding,
    bool_t value
);

void http_reset_client_supported_encoding(
    http_request_headers_t* request_headers
);

#endif
