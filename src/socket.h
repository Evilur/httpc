#ifndef SOCKET_H
#define SOCKET_H

#include <stdint.h>

typedef uint32_t addr_t;
typedef uint16_t port_t;
typedef int32_t socket_fd_t;

int32_t socket_create(socket_fd_t* socket_fd);

int32_t socket_bind(socket_fd_t socket_fd, addr_t addr, port_t port);

int32_t socket_listen(socket_fd_t socket_fd);

int32_t socket_receive(socket_fd_t socket_fd,
                       char* buffer, int32_t buffer_size);

void socket_close(socket_fd_t socket_fd);

#endif
