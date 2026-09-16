#ifndef HASHMAP_H
#define HASHMAP_H

#include <stdint.h>

typedef union hashmap_element {
    int32_t int32;
    void* ptr;
} hashmap_element_t;

typedef struct hashmap_node {
    uint64_t hash;
    void* key;
    int32_t key_size;
    hashmap_element_t data;
} hashmap_node_t;

typedef struct hashmap {
    hashmap_node_t* nodes;
    int32_t capacity;
} hashmap_t;

int32_t hashmap_create(hashmap_t* hashmap, int32_t capacity);

int32_t hashmap_put(hashmap_t* hashmap, void* key, int32_t key_size,
                    hashmap_element_t data);

hashmap_element_t* hashmap_get(hashmap_t* hashmap,
                               void* key, int32_t key_size);

uint64_t hashmap_hash(const void* key, int32_t key_size);

void hashmap_free(const hashmap_t* hashmap);

#endif
