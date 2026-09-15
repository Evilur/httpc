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

    /* Set socket options */
    int32_t opt = 1;
    setsockopt(*socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

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

int32_t socket_receive(const socket_fd_t socket_fd,
                       char* const buffer, int32_t buffer_size) {
    /* Receive the data */
    const int32_t received_size =
        (int32_t)recv(socket_fd, buffer, (uint64_t)buffer_size, 0);

    /* If there is an error */
    if (received_size == -1)
        printerr("Failed to receive a data by socket");

    /* Return the received data size */
    return received_size;
}

int32_t socket_write(const socket_fd_t socket_fd,
                     const char* buffer, int32_t buffer_size) {
    /* Write all the data from the buffer */
    int32_t result = 0;
    while (buffer_size > 0) {
        /* Try to write the data to the buffer */
        const int32_t writed_size =
            (int32_t)write(socket_fd, buffer, (uint64_t)buffer_size);

        /* If the socket is closed */
        if (writed_size == 0) return 1;

        /* If there is an error somewhere */
        if (writed_size == -1) {
            printerr("Failed to write the data to the socket");
            return -1;
        }

        /* Update the data */
        buffer += writed_size;
        buffer_size -= writed_size;
        result += writed_size;
    }

    /* Return the result */
    return result;
}

void socket_close(const socket_fd_t socket_fd) {
    close(socket_fd);
}
