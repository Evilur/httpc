#ifndef SOCKET_H
#define SOCKET_H

#include <stdint.h>

typedef uint16_t port_t;
typedef int32_t socket_fd_t;

socket_fd_t socket_init(const port_t port, socket_fd_t* server_fd);

#endif
