#ifndef SERVER_H
#define SERVER_H

#include "socket.h"

int32_t server_accept_connection(socket_fd_t server_fd,
                                 socket_fd_t* client_fd);

int32_t server_receive_request(socket_fd_t client_fd, char* buffer,
                               int32_t buffer_size, int32_t* buffer_offset);

#endif
