#ifndef HTTP_H
#define HTTP_H

#include "bool.h"
#include "ctrie.h"
#include "hashmap.h"
#include "socket.h"

#include <stdint.h>

#define HTTP_METHOD_SHIFT             (uint16_t)0x0u
#define HTTP_TRANSFER_ENCODING_SHIFT  (uint16_t)0x3u
#define HTTP_CONTENT_ENCODING_SHIFT   (uint16_t)0x4u
#define HTTP_ACCEPT_ENCODING_SHIFT    (uint16_t)0x6u
#define HTTP_EXPECT_SHIFT             (uint16_t)0x9u
#define HTTP_CONNECTION_SHIFT         (uint16_t)0xau

#define HTTP_METHOD_MASK                                                       \
    (uint16_t)(0x7u << HTTP_METHOD_SHIFT)
#define HTTP_TRANSFER_ENCODING_MASK                                            \
    (uint16_t)(0x1u << HTTP_TRANSFER_ENCODING_SHIFT)
#define HTTP_CONTENT_ENCODING_MASK                                             \
    (uint16_t)(0x3u << HTTP_CONTENT_ENCODING_SHIFT)
#define HTTP_ACCEPT_ENCODING_MASK                                              \
    (uint16_t)(0x7u << HTTP_ACCEPT_ENCODING_SHIFT)
#define HTTP_EXPECT_MASK                                                       \
    (uint16_t)(0x1u << HTTP_EXPECT_SHIFT)
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

typedef enum http_expect_type {
    HTTP_EXPECT_NONE         = 0X0U << HTTP_EXPECT_SHIFT,
    HTTP_EXPECT_100_CONTINUE = 0X1U << HTTP_EXPECT_SHIFT
} http_expect_t;

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
     * 1bit:  Expect (none|100-continue)
     * 1bit:  Connection (keep-alive|close)
     */
    uint16_t flags;
} http_request_headers_t;

typedef enum http_supported_headers {
    HTTP_SUPPORTED_ACCEPT_ENCODING,
    HTTP_SUPPORTED_CONNECTION,
    HTTP_SUPPORTED_CONTENT_ENCODING,
    HTTP_SUPPORTED_CONTENT_LENGTH,
    HTTP_SUPPORTED_EXPECT,
    HTTP_SUPPORTED_RANGE,
    HTTP_SUPPORTED_TRANSFER_ENCODING
} http_supported_headers_t;

extern ctrie_node_t http_supported_headers_ctrie;

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

http_expect_t http_get_expect(
    const http_request_headers_t* request_headers
);

void http_set_expect(
    http_request_headers_t* request_headers,
    http_expect_t expect
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
