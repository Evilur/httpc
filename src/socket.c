#include "socket.h"
#include "error.h"

#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

int32_t socket_create(socket_fd_t* const socket_fd) {
    /* Create the socket */
    *socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (*socket_fd == -1) {
        printerr("Failed to initialize a socket");
        return -1;
    }

    /* Return the success code */
    return 0;
}

int32_t socket_bind(const socket_fd_t socket_fd,
                    const addr_t addr,
                    const port_t port) {
    /* Create the address structure */
    struct sockaddr_in sockaddr = {
        .sin_family = AF_INET,
        .sin_port = htons(port),
        .sin_addr.s_addr = addr
    };

    /* Bind the address */
    if (bind(socket_fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) == -1) {
        printerr("Failed to bind the address");
        return -1;
    }

    /* Return the success code */
    return 0;
}

int32_t socket_listen(const socket_fd_t socket_fd) {
    /* Start to listening for connections */
    if (listen(socket_fd, SOMAXCONN) == -1) {
        printerr("Failed to start listening for connections");
        return -1;
    }

    /* Return the success code */
    return 0;
}

void socket_close(socket_fd_t socket_fd) {
    close(socket_fd);
}
