#ifndef HTTPC_HTTP
#define HTTPC_HTTP

typedef char http_method;

#define HTTP_METHOD_GET 0
#define HTTP_METHOD_HEAD 1
#define HTTP_METHOD_NOT_IMPLEMENTED -1

#define HTTP_ERROR_RESPONSE\
"HTTP/1.0 %d\r\n"\
"Content-Length: 0\r\n"\
"\r\n"
#define HTTP_ERROR_RESPONSE_SIZE sizeof(HTTP_ERROR_RESPONSE) + 1

void http_send_error(int client_fd, int e_code);

#endif