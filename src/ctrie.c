#include "ctrie.h"
#include "error.h"
#include "null.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int32_t ctrie_compare_keys(const void* pair1, const void* pair2);

static int32_t ctrie_less_common_prefix(const char* str1, const char* str2);

int32_t ctrie_create(ctrie_node_t* const ctrie,
                     ctrie_key_value_t* const key_values,
                     const int32_t size) {
    /* Sort the array of key->value pairs */
    qsort(key_values, (uint64_t)size,
          sizeof(ctrie_key_value_t), ctrie_compare_keys);

    /* Alloc the memory for the groups */
    int32_t* const groups = malloc(sizeof(int32_t) * (uint64_t)size);
    if (groups == null) {
        printerr("Failed to allocate the memory for the ctrie");
        return -1;
    }
    int32_t* groups_ptr = groups;
    *groups_ptr = 1;

    /* Get the groups sizes */
    for (int i = 1; i < size; ++i)
        if (*key_values[i - 1].key == *key_values[i].key)
            ++*groups_ptr;
        else {
            ++groups_ptr;
            *groups_ptr = 1;
        }
    const uint8_t groups_size = (uint8_t)(groups_ptr - groups + 1);

    /* Alloc the memory for less common prefixes */
    typedef struct lcp {
        const char* str;
        int32_t size;
    } lcp_t;
    lcp_t* const lcps = malloc(sizeof(lcp_t) * (uint64_t)groups_size);
    if (lcps == null) {
        printerr("Failed to allocate the memory for the ctrie");
        free(groups);
        return -1;
    }
    lcp_t* lcps_ptr = lcps;

    /* Get the lcps */
    const ctrie_key_value_t* key_values_ptr = key_values;
    const int32_t* const groups_end = groups + groups_size;
    for (groups_ptr = groups; groups_ptr < groups_end; ++groups_ptr) {
        lcps_ptr->str = key_values_ptr->key;
        lcps_ptr->size = *groups_ptr > 1 ? ctrie_less_common_prefix(
            key_values_ptr->key,
            (key_values_ptr + *groups_ptr - 1)->key
        ) : (int32_t)strlen(key_values_ptr->key);
        ++lcps_ptr;
        key_values_ptr += *groups_ptr;
    }

    /* Set the number of edges */
    ctrie->edges_num = groups_size;

    /* Free the memory */
    free(lcps);
    free(groups);

    /* Return the success code */
    return 0;
}

static int32_t ctrie_compare_keys(const void* const pair1,
                            const void* const pair2) {
    return strcmp(((const ctrie_key_value_t*)pair1)->key,
                  ((const ctrie_key_value_t*)pair2)->key);
}

static int32_t ctrie_less_common_prefix(const char* str1, const char* str2) {
    int32_t diff = 0;
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
        ++str1;
        ++str2;
        ++diff;
    }
    return diff;
}
