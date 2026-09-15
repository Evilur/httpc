#include "util.h"
#include "null.h"

#include <string.h>

char* util_memmem(const char* buffer, const int32_t buffer_size,
                  const char* const pattern, const int32_t pattern_size) {
    /* Get the last possible pointer */
    const char* const buffer_end = buffer + (buffer_size - pattern_size);

    /* Try to find the pattern */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    while (buffer < buffer_end)
        if (memcmp(buffer, pattern, (uint64_t)pattern_size) == 0)
            return (char*)buffer;
        else ++buffer;
#pragma GCC diagnostic pop

    /* If there is no pattern in the buffer */
    return null;
}

int32_t util_hexval(unsigned char chr) {
    if (chr >= '0' && chr <= '9') return chr - '0';
    if (chr >= 'a' && chr <= 'f') return chr - 'a' + 10;
    if (chr >= 'A' && chr <= 'F') return chr - 'A' + 10;
    return -1;
}
