#include "http.h"

int32_t http_handle_request(char* buffer, int32_t size) {
    return *buffer + size;
}
