#include "../properties.h"
#include "arg_handler.h"
#include "error.h"
#include "event_loop.h"
#include "socket.h"

#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
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

    /* Init the event loop and register the server event */
    event_loop_t event_loop;
    if (event_loop_create(&event_loop) == -1 ||
        event_loop_register_event(&event_loop, server_fd, READY_READ) == -1)
        return -1;

    /* Create the array to store the events */
    event_t events[MAX_EVENTS_PER_ITERATION];

    /* Run the event loop */
    for (;;) {
        /* Get events */
        const int32_t events_num = event_loop_wait(&event_loop);
        event_loop_get_events(&event_loop, events, events_num);

        /* Loop through the events */
        for (int32_t i = 0; i < events_num; ++i) {
            /* Get the socket file decryptor from the event */
            const socket_fd_t socket_fd = events[i].socket_fd;

            /* Server socket event */
            if (socket_fd == server_fd) {
            }

            /* Client socket event */
            else {
            }
        }
    }

    /* Close the server socket and the event loop */
    event_loop_close(&event_loop);
    socket_close(server_fd);

    /* Return the success code */
    return 0;
}
