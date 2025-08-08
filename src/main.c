#include "../properties.h"
#include "socket.h"

#include <stdlib.h>

int main(const int argc, const char* const* const argv) {
    /* Get the port to listen to */
    unsigned short port = argc > 1 ? (unsigned short)atoi(argv[1])
                                   : DEFAULT_PORT;
    if (port == 0) port = DEFAULT_PORT;

    /* Try to open the socket connection */
    const int server_fd = socket_listen_port(port);
    if (server_fd == -1) return -1;

    /* Handle all connections */
    for (;;) socket_handle_connection(server_fd);
}