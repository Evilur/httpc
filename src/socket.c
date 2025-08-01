#include "socket.h"
#include "http.h"

#include "../properties.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

int socket_listen_port(const unsigned short port) {
    /* Create a socket */
    const int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("Failed to create a socket");
        return -1;
    }

    /* Set socket options */
    const int socket_opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR,
                   &socket_opt, sizeof(socket_opt)) == -1) {
        perror("Failed to set socket options");
        return -1;
    }

    /* Init in address */
    const struct sockaddr_in server_address = {
        AF_INET,
        htons(port),
        { INADDR_ANY }
    };

    /* Bind the socket to the address */
    if (bind(server_fd,
        (struct sockaddr*)&server_address,
        sizeof(server_address)) == -1) {
        perror("Failed to bind the socket to the address");
        return -1;
    }

    /* Start listening incoming connections */
    if (listen(server_fd, SOMAXCONN) == -1) {
        perror("Failed to listening to port");
        return -1;
    }

    /* Log */
    printf("Start listening to %hu port (http://localhost:%hu)\n", port, port);

    /* Return the server file descriptor */
    return server_fd;
}

void socket_handle_connection(const int server_fd) {
    /* Init a struct to store the client address */
    struct sockaddr_in client_address;
    const int client_addrlen = sizeof(client_address);

    /* Accept the connection */
    const int client_fd = accept(server_fd,
                                 (struct sockaddr*)&client_address,
                                 (socklen_t*)&client_addrlen);
    if (client_fd == -1) {
        perror("Failed to accept the connection\n");
        return;
    }

    /* Read the request line */
    char buffer[BUFFER_SIZE];
    int request_size = read(client_fd, buffer, BUFFER_SIZE);

    /* Get the end of the request line */
    char* const request_line_end = memchr(buffer, '\r', request_size);
    if (request_line_end != NULL) *request_line_end = '\0';

    /* Log the message */
    printf("[%s] %s\n", inet_ntoa(client_address.sin_addr), buffer);

    /* Check the request line */
    const http_method method =
        strncmp(buffer, "GET /", 5) == 0 ? HTTP_METHOD_GET :
        strncmp(buffer, "HEAD /", 6) == 0 ? HTTP_METHOD_HEAD :
        HTTP_METHOD_NOT_IMPLEMENTED;

    /* Check for the right http method */
    if (method == HTTP_METHOD_NOT_IMPLEMENTED) {
        http_send_error(client_fd, 501);
        goto end;
    }

    /* Close the connection */
    end:
    close(client_fd);
}
