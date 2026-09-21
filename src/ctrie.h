#ifndef CTRIE_H
#define CTRIE_H

#include "bool.h"

#include <stdint.h>

typedef struct ctrie_edge ctrie_edge_t;
typedef struct ctrie_node ctrie_node_t;

struct ctrie_edge {
    const char* label;
    ctrie_node_t* child;
};

struct ctrie_node {
    ctrie_edge_t* edges;
    uint8_t edges_num;
    bool_t is_terminal;
};

typedef union ctrie_data {
    int32_t int32;
} ctrie_data_t;

typedef struct ctrie_terminal_node {
    ctrie_edge_t* edges;
    uint8_t edges_num;
    bool_t is_terminal;
    ctrie_data_t data;
} ctrie_terminal_node_t;

typedef struct ctrie_key_value {
    const char* key;
    ctrie_data_t value;
} ctrie_key_value_t;

int32_t ctrie_create(ctrie_node_t* ctrie,
                     ctrie_key_value_t* key_values,
                     int32_t size);

#endif
