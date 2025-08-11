#ifndef HTTPC_HTTP
#define HTTPC_HTTP

enum HTTP_METHOD { GET, NOT_IMPLEMENTED };

void http_return_error(int client_fd, int e_code);

void http_return_redirect(int client_fd, int code, const char* location);

void http_return_file(int client_fd, const char* path, long file_size);

void http_return_directory(int client_fd, const char* path);

#endif