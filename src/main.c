#include "../properties.h"
#include "arg_handler.h"
#include "error.h"
#include "event_loop.h"
#include "http.h"
#include "null.h"
#include "server.h"
#include "socket.h"

#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>

int32_t main(const int32_t argc, const char* const* const argv) {
    /* Init the parameters */
    const char* directory = getcwd(NULL, 0);
    port_t port = DEFAULT_PORT;
    init(argc, argv, &directory, &port);

    /* Init the server web socket and start to listen for connections */
    socket_fd_t server_fd;
    if (socket_create(&server_fd) == -1 ||
        socket_bind(server_fd, INADDR_ANY, port) == -1 ||
        socket_listen(server_fd) == -1)
        return -1;
    printf("Start listening on http://0.0.0.0:%hu\n", port);

    /* Try to init the http handler */
    if (http_init() == -1) return -1;

    /* Create a connection structure */
    server_connection_t server_connection = { .socket_fd = server_fd };

    /* Init the event loop and register the server event */
    event_loop_t event_loop;
    if (event_loop_create(&event_loop) == -1 ||
        event_loop_register_event(&event_loop, READY_READ,
                                  server_fd,
                                  &server_connection) == -1)
        return -1;

    /* Create the array to store the events */
    void* connections[MAX_CONNECTIONS_PER_ITERATION];

    /* Run the event loop */
    for (;;) {
        /* Get events */
        const int32_t events_num = event_loop_wait(&event_loop);
        event_loop_get_connections(&event_loop, connections, events_num);

        /* Loop through the events */
        for (void** connection_ptr = connections,
             * const* const connections_end = connections + events_num;
             connection_ptr < connections_end; ++connection_ptr) {
            /* Get a connection and a fd */
            connection_t* connection = *connection_ptr;
            const socket_fd_t socket_fd = connection->socket_fd;

            /* Server socket event */
            if (socket_fd == server_fd) {
                /* Accept the client connection */
                socket_fd_t client_fd;
                if (server_accept_connection(server_fd, &client_fd) == -1)
                    continue;

                /* Malloc for the new connection */
                connection_t* const new_connection =
                    malloc(sizeof(connection_t));
                if (new_connection == null) {
                    printerr("Failed to allocate the "
                             "memory for a new connection");
                    continue;
                }

                /* Fill the parameters of a new connection */
                new_connection->socket_fd = client_fd;
                new_connection->buffer_filled = 0;
                new_connection->request_headers = (http_request_headers_t) {
                    .uri = null,
                    .range = null,
                    .flags = 0
                };
                new_connection->state = HTTP_CONNECTION_READING_URI;

                /* Register the client fd in the event loop */
                if (event_loop_register_event(&event_loop, READY_READ,
                                              client_fd,
                                              new_connection) == -1) {
                    free(new_connection);
                    socket_close(client_fd);
                }
            }

            /* Client socket event */
            else {
                /* Get the buffer */
                char* const buffer = connection->buffer;
                int32_t* const buffer_filled = &connection->buffer_filled;

                /* Try to receive the request
                 * If the client has closed the connection (1 code)
                 * Or there is an error somewhere (-1 code)
                 * Close the socket, remove the event from the event loop
                 * And free the connection
                 */
                if (server_receive_request(socket_fd, buffer,
                                           sizeof(connection->buffer),
                                           buffer_filled) != 0) {
                    event_loop_remove_event(&event_loop, socket_fd);
                    socket_close(socket_fd);
                    free(connection);
                    continue;
                }

                /* Get the request headers and the connection state */
                http_request_headers_t* const request_headers =
                    &connection->request_headers;
                http_connection_state_t* const connection_state =
                    &connection->state;

                /* Create the buffer_ptr and buffer_size for reading */
                char* buffer_ptr = buffer;
                int32_t buffer_size = *buffer_filled;

                /* Try to handle the request */
                if (*connection_state == HTTP_CONNECTION_READING_URI)
                    switch (http_handle_request_uri(
                        request_headers, socket_fd, &buffer_ptr, &buffer_size
                    )) {
                        case 0:
                            ++*connection_state;
                            break;
                        case 1:
                            if (buffer != buffer_ptr) {
                                memmove(buffer, buffer_ptr,
                                        (uint64_t)buffer_size);
                                *buffer_filled = buffer_size;
                            }
                            break;
                        case -1:
                            break;
                    }
            }
        }
    }

    /* Close the server socket and the event loop */
    event_loop_close(&event_loop);
    socket_close(server_fd);

    /* Return the success code */
    return 0;
}
