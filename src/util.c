#include "util.h"
#include "null.h"

#include <string.h>

char* util_memmem(const char* buffer, const int32_t buffer_size,
                  const char* const pattern, const int32_t pattern_size) {
    /* Try to find the pattern */
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wcast-qual"
    for (const char* const buffer_end = buffer + (buffer_size - pattern_size);
         buffer < buffer_end; ++buffer)
        if (memcmp(buffer, pattern, (uint64_t)pattern_size) == 0)
            return (char*)buffer;
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

bool_t util_strcicmp(const char* str1, const char* str2) {
    /* Loop through strings */
    while (*str1 != '\0' && *str2 != '\0') {
        char c1 = *str1;
        char c2 = *str2;

        if (c1 != c2) {
            /* Invert c1 case */
            if (c1 >= 'A' && c1 <= 'Z')
                c1 += 'a' - 'A';
            else if (c1 >= 'a' && c1 <= 'z')
                c1 -= 'a' - 'A';

            /* Yet another check */
            if (c1 != c2) return 0;
        }

        ++str1;
        ++str2;
    }

    /* Return true */
    return 1;
}

char* util_trim(char* str) {
    while (*str == ' ') ++str;
    return str;
}
