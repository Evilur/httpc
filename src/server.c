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
                               int32_t* const buffer_offset) {
    /* Recieve a request */
    *buffer_offset += socket_receive(client_fd,
                                     buffer + *buffer_offset,
                                     buffer_size - *buffer_offset);

    /* If the connection has been closed */
    if (*buffer_offset == 0) return 1;

    /* If there is an error */
    if (*buffer_offset == -1) return -1;

    /* Return a success code */
    return 0;
}
