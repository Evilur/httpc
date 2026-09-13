#include "error.h"

#include <stdarg.h>
#include <stdio.h>

void printerr(const char* const format, ...) {
    /* Make the next text bold red and print Error word */
    fputs("\033[1;31mError: ", stderr);

    /* Print the formatted message */
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    /* Print the new line character, and reset the text style */
    fputs("\n\033[0m", stderr);
}
