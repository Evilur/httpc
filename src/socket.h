#ifndef HTTPC_SOCKET
#define HTTPC_SOCKET

int socket_listen_port(unsigned short port);

void socket_handle_connection(int server_fd);

#endif