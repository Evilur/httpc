#include "../properties.h"
#include "error.h"
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

/**
 * Init parameters by arguments
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @param directory The pointer to the directory string
 * @param port The pointer to the port variable
 */
static int32_t init_params(const int32_t argc,
                           const char* const* const argv,
                           const char** directory,
                           port_t* port);

/**
 * Print the help message
 */
static void print_help(void);

int32_t main(const int32_t argc, const char* const* const argv) {
    /* Init the parameters */
    const char* directory = getcwd(NULL, 0);
    port_t port = DEFAULT_PORT;
    init_params(argc, argv, &directory, &port);

    /* Init the socket */
    socket_fd_t server_fd;
    if (socket_init(port, &server_fd) == -1) return -1;

    /* Return the success code */
    return 0;
}

static int32_t init_params(const int32_t argc,
                           const char* const* const argv,
                           const char** const directory,
                           port_t* const port) {
    /* Init default values */
    *directory = getcwd(NULL, 0);
    *port = DEFAULT_PORT;

    /* Read arguments */
    for (int32_t i = 1; i < argc; ++i) {
        const char* const arg = argv[i];
        struct stat st;

        /* Check for help arg */
        if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
            print_help();
            return -1;
        }

        /* Check for directory */
        else if (stat(arg, &st) == 0 && S_ISDIR(st.st_mode))
            *directory = arg;

        /* Check for port */
        else {
            const port_t possible_port = (port_t)atoi(arg);
            if (possible_port != 0) *port = possible_port;
        }
    }

    /* Validate the parameters */
    if (directory == NULL) {
        printerr("Failed to get the directory");
        return -1;
    }
    if (port == 0) {
        printerr("Invalid port");
        return -1;
    }

    /* Return the success code */
    return 0;
}

static void print_help(void) {
    puts("\
NAME:\n\
\thttpc - HyperText Transfer Protocol on C\n\
");
}
