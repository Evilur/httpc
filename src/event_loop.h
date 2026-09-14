#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "../properties.h"
#include "socket.h"

#include <stdint.h>
#include <sys/epoll.h>

typedef int32_t epoll_fd_t;
typedef struct epoll_event epoll_event_t;

/**
 * Event struct
 */
typedef struct event {
    socket_fd_t socket_fd;
} event_t;

/**
 * Event loop struct
 */
typedef struct event_loop {
    epoll_fd_t epoll_fd;
    epoll_event_t events[MAX_EVENTS_PER_ITERATION];
} event_loop_t;

/**
 * Event type enum
 */
typedef enum event_type {
    READY_READ = EPOLLIN,
    READY_WRITE = EPOLLOUT
} event_type_t;

/**
 * Create an event loop
 * @param event_loop The struct to store the event_loop
 */
int32_t event_loop_create(event_loop_t* event_loop);

/**
 * Register the event
 * @param even_loop The struct to register the event
 * @param socket_fd The socket file descryptor to listen for events
 * @param event_type The event type to listen
 */
int32_t event_loop_register_event(const event_loop_t* event_loop,
                                  socket_fd_t socket_fd,
                                  event_type_t event_type);

/**
 * Remove the event from the event loop
 * @param even_loop The struct to remove the event
 * @param socket_fd The socket file descryptor to delete
 */
int32_t event_loop_remove_event(const event_loop_t* event_loop,
                                socket_fd_t socket_fd);

/**
 * Wait for events
 * @param event_loop The struct to wait for events
 */
int32_t event_loop_wait(event_loop_t* event_loop);

/**
 * Get events from the last wait
 * @param event_loop The struct to get the events
 * @param events The pointer to store the events array
 */
void event_loop_get_events(const event_loop_t* event_loop,
                           event_t* events, int32_t events_num);

/**
 * Close the event loop
 * @param event_loop The struct to close
 */
void event_loop_close(const event_loop_t* event_loop);

#endif
