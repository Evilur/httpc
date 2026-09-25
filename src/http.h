#ifndef HTTP_H
#define HTTP_H

#include "bool.h"
#include "ctrie.h"
#include "socket.h"

#include <stdint.h>

#define HTTP_CONNECTION_SHIFT         (uint8_t)0x0u
#define HTTP_ACCEPT_ENCODING_SHIFT    (uint8_t)0x1u

#define HTTP_ACCEPT_ENCODING_MASK                                              \
    (uint8_t)(0x7u << HTTP_ACCEPT_ENCODING_SHIFT)
#define HTTP_CONNECTION_MASK                                                   \
    (uint8_t)(0x1u << HTTP_CONNECTION_SHIFT)

typedef enum http_accept_encoding {
    HTTP_ACCEPT_ENCODING_ZSTD = 0x1u << (HTTP_ACCEPT_ENCODING_SHIFT + 0x0u),
    HTTP_ACCEPT_ENCODING_BR   = 0x1u << (HTTP_ACCEPT_ENCODING_SHIFT + 0x1u),
    HTTP_ACCEPT_ENCODING_GZIP = 0x1u << (HTTP_ACCEPT_ENCODING_SHIFT + 0x2u)
} http_accept_encoding_t;

typedef enum http_connection_type {
    HTTP_CONNECTION_CLOSE     = 0x0u << HTTP_CONNECTION_SHIFT,
    HTTP_CONNECTION_KEEPALIVE = 0x1u << HTTP_CONNECTION_SHIFT
} http_connection_type_t;

typedef enum http_request_method {
    HTTP_METHOD_NONE    = 0x0u,
    HTTP_METHOD_GET     = 0x1u,
    HTTP_METHOD_HEAD    = 0x2u,
    HTTP_METHOD_POST    = 0x3u
} http_request_method_t;

typedef enum http_connection_state {
    HTTP_CONNECTION_READING_URI,
    HTTP_CONNECTION_READING_HEADERS,
    HTTP_CONNECTION_SENDING_RESPONSE
} http_connection_state_t;

typedef enum http_supported_headers {
    HTTP_SUPPORTED_HEADER_ACCEPT_ENCODING,
    HTTP_SUPPORTED_HEADER_CONNECTION,
    HTTP_SUPPORTED_HEADER_CONTENT_LENGTH,
    HTTP_SUPPORTED_HEADER_EXPECT,
    HTTP_SUPPORTED_HEADER_RANGE,
    HTTP_SUPPORTED_HEADER_TRANSFER_ENCODING
} http_supported_headers_t;

/**
 * Request headers struct
 */
typedef struct http_request_headers {
    char* uri;
    char* range;

    /**
     * 3bits: Accept-Encoding (gzip, br, zstd)
     * 1bit:  Connection (keep-alive|close)
     */
    uint8_t flags;
} http_request_headers_t;

extern ctrie_t http_supported_methods_ctrie;
extern ctrie_t http_supported_headers_ctrie;
extern ctrie_t http_supported_encoding_ctrie;

int32_t http_init(void);

int32_t http_handle_request_uri(http_request_headers_t* request_headers,
                                socket_fd_t socket_fd,
                                char** buffer_ptr, int32_t* buffer_size);

int32_t http_handle_request_headers(http_request_headers_t* request_headers,
                                    socket_fd_t socket_fd,
                                    char** buffer_ptr, int32_t* buffer_size);

int32_t http_send_default_response(socket_fd_t socket_fd,
                                   char* buffer, int32_t buffer_size,
                                   int32_t status_code,
                                   const char* status_description);

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
