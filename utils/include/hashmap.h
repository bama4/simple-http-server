#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>
#define MAX_HASHMAP_SIZE 4000

typedef struct {
    size_t capacity;
    size_t used;
    void *_contents;
} hashmap_t;

/**
 * @brief      Initializes the hashmap.
 *
 * @param[in]  item_size  The item size
 *
 * @return     { description_of_the_return_value }
 */
hashmap_t *init_hashmap(size_t item_size);

/**
 * @brief      Frees the memory allocated to the given hashmap
 *
 * @param      map   The map
 */
void free_hashmap(hashmap_t *map);

#endif /*HASHMAP_H*/