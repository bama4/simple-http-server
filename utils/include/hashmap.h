#ifndef HASHMAP_H
#define HASHMAP_H

#include "entry.h"
#include "map.h"
#include <stddef.h>
#define MAX_HASHMAP_SIZE 4000
#define MAX_LOAD_CAPACITY 0.75

typedef struct {
    size_t capacity;
    size_t used;
    entry_t *_contents;
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
 * @brief      Converts the data to an unsigned integer value
 *
 * @param      map  The map to calculate the hash value
 * @param      data     The data
 * @param      len      The length of the data
 * @param[in]  max_val  The maximum value
 *
 * @return     Returns the hash value, else -1 if unsuccessful
 */
int hashval(hashmap_t *map, char *data, size_t len);

/**
 * @brief      Inserts the given map (key value pair) into the given hashmap
 *
 * @param      map   The map
 * @param      pair  The pair
 *
 * @return     Returns the index that the pair was inserted to if success, else
 * -1
 */
int insert_hashmap(hashmap_t *map, map_t *pair);

/**
 * @brief      Frees the memory allocated to the given hashmap
 *
 * @param      map   The map
 */
void free_hashmap(hashmap_t *map);

#endif /*HASHMAP_H*/