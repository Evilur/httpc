#include "http.h"

#include "../properties.h"

#include <stdio.h>
#include <sys/socket.h>
#include <sys/sendfile.h>
#include <fcntl.h>
#include <unistd.h>

void http_return_error(const int client_fd, const int e_code) {
    char buffer[HTTP_ERROR_RESPONSE_SIZE];
    sprintf(buffer, HTTP_ERROR_RESPONSE, e_code);
    send(client_fd, buffer, HTTP_ERROR_RESPONSE_SIZE, 0);
}

void http_return_file(const int client_fd,
                      const char* path,
                      const long file_size) {
    /* Send headers */
    char headers_buffer[HTTP_OK_RESPONSE_SIZE];
    const int header_size = sprintf(headers_buffer, HTTP_OK_RESPONSE, file_size);
    send(client_fd, headers_buffer, header_size, 0);

    /* Open the file for reading */
    const int file_fd = open(path, O_RDONLY);

    /* Read the data to the buffer and send it to the socket */
    char buffer[BUFFER_SIZE];
    int read_size;
    while ((read_size = read(file_fd, buffer, BUFFER_SIZE)) > 0)
        send(client_fd, buffer, read_size, 0);
}
