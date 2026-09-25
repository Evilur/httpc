#ifndef UTIL_H
#define UTIL_H

#include "bool.h"
#include <stdint.h>

char* util_memmem(const char* buffer, int32_t buffer_size,
                  const char* pattern, int32_t pattern_size);

int32_t util_hexval(unsigned char chr);

bool_t util_strcicmp(const char* str1, const char* str2);

char* util_trim(char* str);

#endif
