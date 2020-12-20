#include "hashmap.h"
#include <stdlib.h>

/**
 * @brief      Initializes the hashmap.
 *
 * @param[in]  item_size  The item size
 *
 * @return     { description_of_the_return_value }
 */
hashmap_t *init_hashmap(size_t item_size) {

    if (item_size > MAX_HASHMAP_SIZE) {
        // item size requested exceeds item size
        return NULL;
    }

    hashmap_t *tmp = malloc(sizeof(hashmap_t));
    if (tmp == NULL) {
        // malloc failed
        return NULL;
    }

    tmp->_contents = NULL;
    tmp->capacity = item_size;
    tmp->used = 0;
    return tmp;
}

/**
 * @brief      Frees the memory allocated to the given hashmap
 *
 * @param      map   The map
 */
void free_hashmap(hashmap_t *map) {
    if (map == NULL) {
        return;
    }

    // Free contents array
    free(map->_contents);
    map->_contents = NULL;

    map->capacity = 0;
    map->used = 0;
    free(map);
}