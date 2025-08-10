#include "../properties.h"
#include "socket.h"

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>

int main(const int argc, const char* const* const argv) {
    /* Get the port to listen to */
    unsigned short port = argc > 1 ? (unsigned short)atoi(argv[1])
                                   : DEFAULT_PORT;
    if (port == 0) port = DEFAULT_PORT;

    /* Try to open the socket connection */
    const int server_fd = socket_listen_port(port);
    if (server_fd == -1) return -1;

#if NON_BLOCKING
    /* Ignore SIGCHLD to avoid zombie children */
    signal(SIGCHLD, SIG_IGN);
#endif

    /* Handle all connections */
    for (;;) {
        /* Init a struct to store the client address */
        struct sockaddr_in client_address;
        int client_addrlen = sizeof(client_address);

        /* Accept the connection */
        const int client_fd = accept(server_fd,
                                     (struct sockaddr*)&client_address,
                                     (socklen_t*)&client_addrlen);

        /* Check the descriptor */
        if (client_fd == -1) {
            perror("Failed to accept the connection");
            return -1;
        }

        /* Set the timeout */
        struct timeval timeout = { .tv_sec = TIMEOUT_SECONDS };
        if (setsockopt(client_fd, SOL_SOCKET, SO_RCVTIMEO,
                       &timeout, sizeof(timeout)) == -1) {
            perror("Failed to set the timeout");
            return -1;
       }

#if NON_BLOCKING
        /* Fork the process */
        const int pid = fork();

        /* If it is impossible to fork the program */
        if (pid == -1) {
            perror("Failed to fork the process");
            return -1;
        }

        /* If it is a child */
        if (pid == 0) {
            /* Close the server descriptor */
            close(server_fd);

            /* Handle this connection */
            socket_handle_connection(client_fd,
                                     inet_ntoa(client_address.sin_addr));

            /* Close the connection */
            close(client_fd);

            /* Exit the program */
            return 0;
        }
#else
        /* Handle this connection */
        socket_handle_connection(client_fd, inet_ntoa(client_address.sin_addr));
#endif

        /* If it is a parent process (or hasn't been forked),
         * close the client descriptor */
        close(client_fd);
    }
}