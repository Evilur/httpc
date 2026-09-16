#ifndef EVENT_LOOP_H
#define EVENT_LOOP_H

#include "../properties.h"
#include "http.h"
#include "socket.h"

#include <stdint.h>
#include <sys/epoll.h>

typedef int32_t epoll_fd_t;
typedef struct epoll_event epoll_event_t;

/**
 * Server connection struct
 */
typedef struct server_connection {
    socket_fd_t socket_fd;
} server_connection_t;

/**
 * Client connection struct
 */
typedef struct connection {
    socket_fd_t socket_fd;
    char buffer[MAX_BUFFER_SIZE];
    int32_t buffer_filled;
    http_request_headers_t request_headers;
    http_connection_state_t state;
} connection_t;

/**
 * Event loop struct
 */
typedef struct event_loop {
    epoll_fd_t epoll_fd;
    epoll_event_t events[MAX_CONNECTIONS_PER_ITERATION];
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
 * @param event The event which will be returned in the loop
 */
int32_t event_loop_register_event(const event_loop_t* event_loop,
                                  event_type_t event_type,
                                  socket_fd_t socket_fd,
                                  void* connection);

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
void event_loop_get_connections(event_loop_t* event_loop,
                                void** connections,
                                int32_t connections_num);

/**
 * Close the event loop
 * @param event_loop The struct to close
 */
void event_loop_close(const event_loop_t* event_loop);

#endif
