#ifndef CTRIE_H
#define CTRIE_H

#include "bool.h"

#include <stdint.h>

typedef struct ctrie_node ctrie_node_t;

typedef struct ctrie {
    ctrie_node_t* childs;
    uint8_t childs_num;
} ctrie_t;

typedef union ctrie_data {
    int32_t int32;
} ctrie_data_t;

struct ctrie_node {
    const char* label;
    ctrie_node_t* childs;
    uint8_t childs_num;
    bool_t is_terminal;
    ctrie_data_t data;
};

typedef struct ctrie_key_value {
    const char* key;
    ctrie_data_t value;
} ctrie_key_value_t;

int32_t ctrie_create(ctrie_t* ctrie,
                     ctrie_key_value_t* key_values,
                     int32_t size);

ctrie_data_t* ctrie_get(const ctrie_t* ctrie,
                        char** key,
                        char eol);

#endif
