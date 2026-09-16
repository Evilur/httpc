#include "hashmap.h"
#include "error.h"
#include "null.h"

#include <stdlib.h>
#include <string.h>

int32_t hashmap_create(hashmap_t* const hashmap, int32_t capacity) {
    /* Increase the capacity */
    capacity = (int32_t)((float)capacity * 1.75f);

    /* Init the hashmap */
    *hashmap = (hashmap_t) {
        .nodes = malloc(sizeof(hashmap_node_t) * (uint64_t)capacity),
        .capacity = capacity
    };

    /* Check for malloc result */
    if (hashmap->nodes == null) {
        printerr("Failed to allocate the memory for a new hashmap");
        return -1;
    }

    /* Init deafult values */
    for (hashmap_node_t* nodes_ptr = hashmap->nodes,
         * const nodes_end = nodes_ptr + hashmap->capacity;
         nodes_ptr < nodes_end;
         ++nodes_ptr)
        nodes_ptr->hash = 0;

    /* Return the success code */
    return 0;
}

int32_t hashmap_put(hashmap_t* const hashmap,
                    void* const key, const int32_t key_size,
                    const hashmap_element_t data) {
    /* Calculate the hash */
    const uint64_t hash = hashmap_hash(key, key_size);

    /* Calculate the index number from the hash */
    const int32_t index = (int32_t)(hash % (uint64_t)hashmap->capacity);

    /* Get the nodes */
    hashmap_node_t* nodes = hashmap->nodes;

    /* Copy the key */
    uint8_t* key_clone = malloc((uint64_t)key_size);
    memcpy(key_clone, key, (uint64_t)key_size);

    /* If the cell is empty */
    if (nodes[index].hash == 0) {
        /* Just write the data there */
        nodes[index] = (hashmap_node_t) {
            .hash = hash,
            .key = key_clone,
            .key_size = key_size,
            .data = data
        };

        /* Return the success code */
        return 0;
    }

    /* If the cell is not empty
     * Loop through the nodes to find the first empty */
    for (hashmap_node_t* node_ptr = nodes + index + 1,
         * const node_end = nodes + hashmap->capacity;
         node_ptr < node_end;
         ++node_ptr) {
        /* If we found an empty cell */
        if (node_ptr->hash == 0) {
            /* Write the data to the empty cell */
            *node_ptr = (hashmap_node_t) {
                .hash = hash,
                .key = key_clone,
                .key_size = key_size,
                .data = data
            };

            /* Return the success code */
            return 0;
        }
    }
    for (hashmap_node_t* node_ptr = nodes,
         * const node_end = nodes + index;
         node_ptr < node_end;
         ++node_ptr) {
        /* If we found an empty cell */
        if (node_ptr->hash == 0) {
            /* Write the data to the empty cell */
            *node_ptr = (hashmap_node_t) {
                .hash = hash,
                .key = key_clone,
                .key_size = key_size,
                .data = data
            };

            /* Return the success code */
            return 0;
        }
    }

    /* There are no free cells,
     * Return the code -1 */
    return -1;
}

hashmap_element_t* hashmap_get(hashmap_t* const hashmap,
                               void* const key, const int32_t key_size) {
    /* Calculate the hash */
    const uint64_t hash = hashmap_hash(key, key_size);

    /* Calculate the index number from the hash */
    const int32_t index = (int32_t)(hash % (uint64_t)hashmap->capacity);

    /* Get the nodes */
    hashmap_node_t* nodes = hashmap->nodes;

    /* Compare the hash and the key */
    hashmap_node_t* const node = nodes + index;
    if (node->hash == 0) return null;
    if (node->hash == hash &&
        node->key_size == key_size &&
        memcmp(node->key, key, (uint64_t)key_size) == 0)
        return &node->data;

    /* If the element is not in its index cell
     * Loop through the nodes to find the first element */
    for (hashmap_node_t* node_ptr = nodes + index + 1,
         * const node_end = nodes + hashmap->capacity;
         node_ptr < node_end;
         ++node_ptr) {
        /* Compare the hash and the key */
        if (node_ptr->hash == 0) return null;
        if (node_ptr->hash == hash &&
            node_ptr->key_size == key_size &&
            memcmp(node_ptr->key, key, (uint64_t)key_size) == 0)
            return &node_ptr->data;
    }
    for (hashmap_node_t* node_ptr = nodes,
         * const node_end = nodes + index;
         node_ptr < node_end;
         ++node_ptr) {
        /* Compare the hash and the key */
        if (node_ptr->hash == 0) return null;
        if (node_ptr->hash == hash &&
            node_ptr->key_size == key_size &&
            memcmp(node_ptr->key, key, (uint64_t)key_size) == 0)
            return &node_ptr->data;
    }

    /* If there is no such and element, return null */
    return null;
}

uint64_t hashmap_hash(const void* const key, const int32_t key_size) {
    /* Start with my favourite prime number */
    uint64_t hash = 751;

    /* Calc the hash */
    for (const uint8_t* data_ptr = (const uint8_t*)key,
         * const data_end = data_ptr + key_size;
         data_ptr < data_end;
         ++data_ptr)
        hash = (hash << 5) - hash + *data_ptr;

    /* Return the hash */
    return hash;
}

void hashmap_free(const hashmap_t* hashmap) {
    free(hashmap->nodes);
}
