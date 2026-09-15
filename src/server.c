#include "server.h"
#include "error.h"
#include "null.h"

#include <sys/socket.h>

int32_t server_accept_connection(const socket_fd_t server_fd,
                                 socket_fd_t* const client_fd) {
    /* Accept the connection */
    *client_fd = accept(server_fd, null, null);
    if (*client_fd == -1) {
        printerr("Failed to accept the connection");
        return -1;
    }

    /* Return the success code */
    return 0;
}

int32_t server_receive_request(socket_fd_t client_fd, char* const buffer,
                               const int32_t buffer_size,
                               int32_t* const buffer_filled) {
    /* Recieve a request */
    const int32_t received_size = socket_receive(client_fd,
                                                 buffer + *buffer_filled,
                                                 buffer_size - *buffer_filled);

    /* If the connection has been closed */
    if (received_size == 0) return 1;

    /* If there is an error */
    if (received_size == -1) return -1;

    /* Update the buffer_filled variable */
    *buffer_filled += received_size;

    /* Return a success code */
    return 0;
}
