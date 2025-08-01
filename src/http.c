#include "http.h"

#include <stdio.h>
#include <sys/socket.h>

void http_send_error(const int client_fd, const int e_code) {
    char buffer[HTTP_ERROR_RESPONSE_SIZE];
    sprintf(buffer, HTTP_ERROR_RESPONSE, e_code);
    send(client_fd, buffer, HTTP_ERROR_RESPONSE_SIZE, 0);
}