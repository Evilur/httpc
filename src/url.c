#include "url.h"

static int url_hex_to_int(char hex);

int url_decode(char* encoded) {
    /* Check the input */
    if (!encoded) return -1;

    /* Write the data to the same string
     * (because the decoded string can't be larger than encoded) */
    char* decoded = encoded;

    /* Decode the string */
    while (*encoded != '\0') {
        /* Get the current char */
        const char current_char = *encoded++;

        /* If it may be url sequence */
        if (current_char == '%') {
            /* Get next two symbols */
            const int high = url_hex_to_int(encoded[0]);
            const int low = url_hex_to_int(encoded[1]);

            /* Check next two symbols */
            if (high == -1 || low == -1) *decoded++ = '%';
            else {
                *decoded++ = (char)(high * 16 + low);
                encoded += 2;
            }
        }
        /* If it is space character */
        else if (current_char == '+') *decoded++ = ' ';
        /* If it is regular character */
        else *decoded++ = current_char;
    }

    /* Insert the null char */
    *decoded = '\0';

    /* Return the success code */
    return 0;
}

static int url_hex_to_int(const char hex) {
    if (hex >= '0' && hex <= '9') return hex - '0';
    if (hex >= 'A' && hex <= 'F') return hex - 'A' + 10;
    if (hex >= 'a' && hex <= 'f') return hex - 'a' + 10;
    return -1;
}