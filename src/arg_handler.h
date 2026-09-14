#ifndef ARG_HANDLER_H
#define ARG_HANDLER_H

#include "socket.h"

#include <stdint.h>

/**
 * Init parameters by arguments
 * @param argc The number of arguments
 * @param argv The array of arguments
 * @param directory The pointer to the directory string
 * @param port The pointer to the port variable
 */
int32_t init(const int32_t argc,
             const char* const* const argv,
             const char** directory,
             port_t* port);

/**
 * Print the help message
 */
void print_help(void);

#endif
