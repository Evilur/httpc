#include "ctrie.h"
#include "error.h"
#include "null.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int32_t ctrie_compare_keys(const void* pair1, const void* pair2);

static int32_t ctrie_longest_common_prefix(const char* str1, const char* str2);

static bool_t ctrie_are_equals(const char** str1, const char* str2, char eol);

int32_t ctrie_create(ctrie_t* const ctrie,
                     ctrie_key_value_t* const key_values,
                     const int32_t size) {
    /* Check for nullptr */
    if (ctrie == null) {
        printerr("Ctrie object cannot be nullptr");
        return -1;
    }
    if (key_values == null) {
        printerr("Ctrie array cannot be nullptr");
        return -1;
    }

    /* Check the size */
    if (size <= 0) {
        printerr("Ctrie array cannot be less or equal 0");
        return -1;
    }

    /* Sort the array of key->value pairs */
    qsort(key_values, (uint64_t)size,
          sizeof(ctrie_key_value_t), ctrie_compare_keys);

    /* Check for duplicates */
    if (*key_values->key == '\0') {
        printerr("All keys lengths must be more than 0");
        return -1;
    }
    for (const ctrie_key_value_t* key_values_ptr = key_values + 1,
         * const key_values_end = key_values + size;
         key_values_ptr < key_values_end;
         ++key_values_ptr) {
        if (strcmp((key_values_ptr - 1)->key, key_values_ptr->key) == 0) {
            printerr("Duplicate found in the ctrie array");
            return -1;
        }
    }

    /* The struct to temporary store the raw tree */
    typedef struct raw_node raw_node_t;
    struct raw_node {
        ctrie_key_value_t* sources;
        int32_t sources_num;
        const char* label;
        int32_t label_length;
        raw_node_t* childs;
        uint8_t childs_num;
        bool_t is_terminal;
        ctrie_node_t* permanent_node;
    };

    /* Create the root node */
    raw_node_t root_node = {
        .sources = key_values,
        .sources_num = size,
        .label = null,
        .label_length = 0,
        .is_terminal = 0,
        .permanent_node = null
    };
    if (root_node.sources == null) {
        printerr("Failed to allocate the memory for the ctrie");
        return -1;
    }

    /* Create variables to calculate the future buffer size */
    uint32_t all_labels_length = 0;
    uint32_t all_nodes_size = 0;

    /* Alloc the memory for the nodes stack */
    raw_node_t** const nodes_stack =
        malloc(sizeof(raw_node_t*) * (uint64_t)size);
    if (nodes_stack == null) {
        printerr("Failed to allocate the memory for the ctrie");
        return -1;
    }

    /* Put the first element to the stack */
    *nodes_stack = &root_node;

    /* While there is at least one entry in the stack, handle it */
    for (int32_t nodes_stack_size = 1;
         nodes_stack_size > 0;) {
        /* Get the current node and remove the pointer from the stack */
        raw_node_t* current_node = nodes_stack[nodes_stack_size - 1];
        --nodes_stack_size;

        /* Alloc the memory for the groups */
        int32_t* const groups = malloc(sizeof(int32_t) *
                                       (uint64_t)current_node->sources_num);
        if (groups == null) {
            printerr("Failed to allocate the memory for the ctrie");
            goto bad_end;
        }
        int32_t* groups_ptr = groups;
        *groups_ptr = 1;

        /* Get the groups sizes */
        for (const ctrie_key_value_t* source_ptr = current_node->sources + 1,
             * const source_end = current_node->sources +
                                  current_node->sources_num;
             source_ptr < source_end;
             ++source_ptr)
            if (*(source_ptr - 1)->key == *source_ptr->key)
                ++*groups_ptr;
            else {
                ++groups_ptr;
                *groups_ptr = 1;
            }
        const uint64_t groups_num = (uint8_t)(groups_ptr - groups + 1);

        /* Allocate the memory for childs */
        current_node->childs = malloc(sizeof(raw_node_t) * groups_num);
        if (current_node->childs == null) {
            printerr("Failed to allocate the memory for the ctrie");
            free(groups);
            current_node->childs_num = 0;
            goto bad_end;
        }
        current_node->childs_num = (uint8_t)groups_num;

        /* Get the lcps */
        raw_node_t* childs_ptr = current_node->childs;
        ctrie_key_value_t* sources_ptr = current_node->sources;
        const int32_t* const groups_end = groups + groups_num;
        for (groups_ptr = groups; groups_ptr < groups_end; ++groups_ptr) {
            childs_ptr->permanent_node = null;
            childs_ptr->childs = null;
            childs_ptr->childs_num = 0;

            /* Set the label */
            childs_ptr->label = sources_ptr->key;
            childs_ptr->label_length = *groups_ptr > 1 ?
                ctrie_longest_common_prefix(
                sources_ptr->key,
                (sources_ptr + *groups_ptr - 1)->key
            ) : (int32_t)strlen(sources_ptr->key);
            all_labels_length += (uint32_t)childs_ptr->label_length + 1;

            /* Set the sources */
            childs_ptr->is_terminal =
                *(sources_ptr->key + childs_ptr->label_length) == '\0';
            all_nodes_size += (uint32_t)sizeof(ctrie_node_t);
            if (childs_ptr->is_terminal) {
                --*groups_ptr;
                ++sources_ptr;
            }
            childs_ptr->sources = sources_ptr;
            childs_ptr->sources_num = *groups_ptr;
            sources_ptr += *groups_ptr;
            for (ctrie_key_value_t* child_sources_ptr =
                    childs_ptr->sources,
                 * const child_sources_end =
                 childs_ptr->sources + *groups_ptr;
                 child_sources_ptr < child_sources_end;
                 ++child_sources_ptr)
                 child_sources_ptr->key += childs_ptr->label_length;
            if (*groups_ptr > 0) {
                /* Add the child to the stack */
                nodes_stack[nodes_stack_size] = childs_ptr;
                ++nodes_stack_size;
            } else {
                childs_ptr->childs = null;
                childs_ptr->childs_num = 0;
            }

            /* Update the pointers */
            ++childs_ptr;
        }

        /* Free the memory */
        free(groups);
    }

    {
        /* Create a huge buffer to store all the ctrie */
        void* const buffer = malloc(all_labels_length + all_nodes_size);
        if (buffer == null) {
            printerr("Failed to allocate the memory for the ctrie");
            goto bad_end;
        }
        ctrie_node_t* nodes_buffer_ptr = buffer;
        char* labels_buffer_ptr = (char*)buffer + all_nodes_size;

        /* Store the entire ctrie to this buffer */
        *nodes_stack = &root_node;
        for (int32_t nodes_stack_size = 1;
             nodes_stack_size > 0;) {
            raw_node_t* current_node = nodes_stack[nodes_stack_size - 1];

            /* First visit */
            if (current_node->sources_num != 0) {
                /* Free the fields */
                current_node->sources_num = 0;

                /* Set the childs array */
                if (current_node->permanent_node != null)
                    current_node->permanent_node->childs = nodes_buffer_ptr;

                /* Add all the childs to the stack */
                for (raw_node_t* childs_ptr = current_node->childs,
                     * const childs_end = current_node->childs +
                                          current_node->childs_num;
                     childs_ptr < childs_end;
                     ++childs_ptr) {
                    /* Save the data */
                    memcpy(labels_buffer_ptr,
                           childs_ptr->label,
                           (size_t)childs_ptr->label_length);
                    labels_buffer_ptr[childs_ptr->label_length] = '\0';
                    *nodes_buffer_ptr = (ctrie_node_t) {
                        .label = labels_buffer_ptr,
                        .childs = null,
                        .childs_num = childs_ptr->childs_num,
                        .is_terminal = childs_ptr->is_terminal
                    };

                    /* Save the data */
                    if (nodes_buffer_ptr->is_terminal)
                        nodes_buffer_ptr->data = childs_ptr->sources->value;

                    /* Add all the childs to the stack */
                    if (childs_ptr->childs_num > 0) {
                        childs_ptr->permanent_node = nodes_buffer_ptr;
                        nodes_stack[nodes_stack_size] = childs_ptr;
                        ++nodes_stack_size;
                    }

                    /* Increase pointers */
                    ++nodes_buffer_ptr;
                    labels_buffer_ptr += childs_ptr->label_length + 1;
                }
            }

            /* Second visit */
            else {
                --nodes_stack_size;
                free(current_node->childs);
            }
        }

        /* Save the childs pointer */
        ctrie->childs = buffer;
        ctrie->childs_num = root_node.childs_num;

        /* Free the memory */
        free(nodes_stack);

        /* Return the success code */
        return 0;
    }
bad_end:;
    /* Free the memory */
    *nodes_stack = &root_node;
    for (int32_t nodes_stack_size = 1;
         nodes_stack_size > 0;) {
        raw_node_t* current_node = nodes_stack[nodes_stack_size - 1];

        /* First visit */
        if (current_node->sources_num != 0) {
            /* Free the fields */
            current_node->sources_num = 0;

            /* Add all the childs to the stack */
            for (raw_node_t* childs_ptr = current_node->childs,
                 * const childs_end = current_node->childs +
                                      current_node->childs_num;
                 childs_ptr < childs_end;
                 ++childs_ptr) {
                nodes_stack[nodes_stack_size] = childs_ptr;
                ++nodes_stack_size;
            }
        }

        /* Second visit */
        else {
            free(current_node->childs);
            --nodes_stack_size;
        }
    }

    /* Free the memory */
    free(nodes_stack);

    /* Return the error code */
    return -1;
}

static int32_t ctrie_compare_keys(const void* const pair1,
                            const void* const pair2) {
    return strcmp(((const ctrie_key_value_t*)pair1)->key,
                  ((const ctrie_key_value_t*)pair2)->key);
}

static int32_t ctrie_longest_common_prefix(const char* str1, const char* str2) {
    int32_t diff = 0;
    while (*str1 != '\0' && *str2 != '\0' && *str1 == *str2) {
        ++str1;
        ++str2;
        ++diff;
    }
    return diff;
}

ctrie_data_t* ctrie_get(const ctrie_t* const ctrie,
                        const char* key,
                        const char eol) {
    /* Go throught the tree to find the entry */
    for (ctrie_node_t* nodes_ptr = ctrie->childs,
         * nodes_end = ctrie->childs + ctrie->childs_num;
         nodes_ptr < nodes_end;) {
        if (ctrie_are_equals(&key, nodes_ptr->label, eol)) {
            if (nodes_ptr->is_terminal && key[0] == eol)
                return &nodes_ptr->data;
            if (nodes_ptr->childs_num > 0) {
                if (nodes_ptr->childs == null) return null;
                nodes_end = nodes_ptr->childs + nodes_ptr->childs_num;
                nodes_ptr = nodes_ptr->childs;
                if (nodes_ptr == null) return null;
                continue;
            }
        }
        ++nodes_ptr;
    }

    /* Return the null */
    return null;
}

static bool_t ctrie_are_equals(const char** str1,
                               const char* str2,
                               const char eol) {
    /* Tempotaty pointer */
    const char* str1_ptr = *str1;

    /* Loop through strings */
    while (str1_ptr[0] != eol && str1_ptr[0] != '\0' && str2[0] != '\0') {
        if (str1_ptr[0] != str2[0]) return 0;
        ++str1_ptr;
        ++str2;
    }

    /* str2 should end with '\0' */
    if (str2[0] != '\0') {
        return 0;
    }

    /* Update the original pointer */
    *str1 = str1_ptr;

    /* Return true */
    return 1;
}
