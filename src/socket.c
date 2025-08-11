#include "../properties.h"
#include "socket.h"
#include "http.h"
#include "url.h"
#include "string.h"

#include <stdio.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

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
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr = { INADDR_ANY }
    };

    /* Bind the socket to the address */
    if (bind(server_fd,
        (const struct sockaddr*)&server_address,
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
    printf("Start listening to %hu port (http://0.0.0.0:%hu)\n", port, port);

    /* Return the server file descriptor */
    return server_fd;
}

void socket_handle_connection(const int client_fd, const char* ip_address) {
    /* Read the request line */
    char buffer[BUFFER_SIZE];
    const long request_size = read(client_fd, buffer, BUFFER_SIZE);
    if (request_size == -1) return;

    /* Get the end of the request line */
    char* const request_line_end = memchr(buffer,
                                          '\r',
                                          (unsigned long)request_size);
    if (request_line_end != NULL) *request_line_end = '\0';

    /* Log the message */
    printf("[%s] %s\n", ip_address, buffer);

    /* Check the request line */
    const enum HTTP_METHOD method = strncmp(buffer, "GET /", 5) == 0 ?
        GET : NOT_IMPLEMENTED;

    /* Check for the right http method */
    if (method == NOT_IMPLEMENTED) {
        http_return_error(client_fd, 501);
        return;
    }

    /* Get the path to the file from the request */
    char* const path = buffer + 3;
    *path = '.';
    char* path_end = strchr(path, ' ');
    if (path_end != NULL) *path_end = '\0';
    else path_end = path + strlen(path);

    /* Decode the url string */
    url_decode(path);

    /* Try to find '/../' in the path */
    if (strstr(path, "/../") != NULL) {
        http_return_error(client_fd, 403);
        return;
    }

    /* Check the file for existence */
    if (access(path, F_OK) == -1) {
        http_return_error(client_fd, 404);
        return;
    }

    /* Check for permissions */
    if (access(path, R_OK) == -1) {
        http_return_error(client_fd, 403);
        return;
    }

    /* Get file stat */
    struct stat file_stat;
    stat(path, &file_stat);

    /* If this is a regular file */
    if (S_ISREG(file_stat.st_mode)) {
        http_return_file(client_fd, path, file_stat.st_size);
        return;
    }

    /* If the file is a directory */
    if (S_ISDIR(file_stat.st_mode)) {
        /* Check for '/' char in the end */
        if (path_end[-1] != '/') {
            strcpy(path_end, "/");  // Add '/' char at the end
            http_return_redirect(client_fd, 301, path + 1);
            return;
        }

#if READ_INDEX_HTML
        /* Check for index.html existence */
        strcpy(path_end, "index.html");
        if (access(path, R_OK) != -1) {
            stat(path, &file_stat);
            http_return_file(client_fd, path, file_stat.st_size);
            return;
        /* Reset the path */
        } else *path_end = '\0';
#endif

        /* Else just return the directory listing */
        http_return_directory(client_fd, path);
        return;
    }

    /* If it is not a file or a directory */
    http_return_error(client_fd, 501);
}