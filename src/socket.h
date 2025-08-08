#ifndef HTTPC_SOCKET
#define HTTPC_SOCKET

int socket_listen_port(unsigned short port);

void socket_handle_connection(int client_fd, const char* ip_address);

#endif