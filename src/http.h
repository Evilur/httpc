#ifndef HTTPC_HTTP
#define HTTPC_HTTP

typedef char http_method;

#define HTTP_METHOD_GET 0
#define HTTP_METHOD_NOT_IMPLEMENTED -1

#define HTTP_ERROR_RESPONSE \
"HTTP/1.0 %d\r\n"\
"Content-Length: 0\r\n"\
"\r\n"
#define HTTP_ERROR_RESPONSE_SIZE sizeof(HTTP_ERROR_RESPONSE) + 1

#define HTTP_OK_RESPONSE \
"HTTP/1.0 200 OK\r\n"\
"Content-Length: %ld\r\n"\
"\r\n"
#define HTTP_OK_RESPONSE_SIZE sizeof(HTTP_OK_RESPONSE) + 24

#define HTTP_OK_RESPONSE_BODY_HEAD \
"<h1>Directory listing for %s</h1>"\
"<hr>"\
"<ul>"\
"<li><a href='../'>../</a></li>"

void http_return_error(int client_fd, int e_code);

void http_return_file(int client_fd, const char* path, long file_size);

void http_return_directory(int client_fd, const char* path);

#endif