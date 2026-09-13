#include "socket.h"
#include "error.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

socket_fd_t socket_init(const port_t port,
                        socket_fd_t* const server_fd) {
    /* Create the socket */
    *server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (*server_fd == -1) {
        printerr("Failed to initialize a socket");
        return 1;
    }

    /* Create the address 0.0.0.0:port structure */
    struct sockaddr_in addr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = INADDR_ANY
    };

    /* Bind the address */
    if (bind(*server_fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        printerr("Failed to bind the address");
        close(*server_fd);
        return 1;
    }

    /* Start to listening for connections */
    if (listen(*server_fd, SOMAXCONN) == -1) {
        printerr("Failed to start listening for connections");
        close(*server_fd);
        return 1;
    }

    /* Return the success code */
    return 0;
}
