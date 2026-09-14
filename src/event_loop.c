#include "event_loop.h"
#include "error.h"
#include "null.h"

#include <sys/epoll.h>
#include <unistd.h>

int32_t event_loop_create(event_loop_t* const event_loop) {
    /* Try to create the epoll */
    event_loop->epoll_fd = epoll_create1(0);
    if (event_loop->epoll_fd == null) {
        printerr("Failed to initialize an epoll");
        return -1;
    }

    /* Return a success code */
    return 0;
}

int32_t event_loop_register_event(const event_loop_t* const event_loop,
                                  const event_type_t event_type,
                                  const socket_fd_t socket_fd,
                                  void* const connection) {
    /* Create an event */
    epoll_event_t epoll_event = {
        .events = event_type,
        .data.ptr = connection
    };

    /* Try to register the event */
    if (epoll_ctl(event_loop->epoll_fd, EPOLL_CTL_ADD,
                  socket_fd, &epoll_event) == -1) {
        printerr("Failed to register the epoll event");
        return -1;
    }

    /* Return a success code */
    return 0;
}

int32_t event_loop_remove_event(const event_loop_t* const event_loop,
                                const socket_fd_t socket_fd) {
    /* Try to remove the event */
    if (epoll_ctl(event_loop->epoll_fd, EPOLL_CTL_DEL,
                  socket_fd, null) == -1) {
        printerr("Failed to delete the epoll event");
        return -1;
    }

    /* Return the success code */
    return 0;
}

int32_t event_loop_wait(event_loop_t* const event_loop) {
    return epoll_wait(event_loop->epoll_fd,
                      event_loop->events,
                      MAX_CONNECTIONS_PER_ITERATION, -1);
}

void event_loop_get_connections(event_loop_t* const event_loop,
                                void** connections,
                                int32_t connections_num) {
    epoll_event_t* epoll_events = event_loop->events;
    while (connections_num > 0) {
        *connections = epoll_events->data.ptr;
        ++connections;
        ++epoll_events;
        --connections_num;
    }
}

void event_loop_close(const event_loop_t* const event_loop) {
    close(event_loop->epoll_fd);
}
