#include "../properties.h"
#include "arg_handler.h"
#include "error.h"

#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/epoll.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <unistd.h>

int32_t init(const int32_t argc,
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

void print_help(void) {
    puts("\
NAME:\n\
\thttpc - HyperText Transfer Protocol on C\n\
");
}
