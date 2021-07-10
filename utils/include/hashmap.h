#ifndef HASHMAP_H
#define HASHMAP_H

#include "entry.h"
#include "map.h"
#include <stddef.h>
#define MAX_HASHMAP_SIZE 4000
#define MAX_LOAD_CAPACITY 0.75

typedef struct {
    size_t capacity;    /* The capacity of the hashmap */
    size_t used;        /* The actual space used in the hashmap */
    entry_t *_contents; /* The array of entries in the hashmap */
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
 *             Uses a linear probing method for resolving collisions
 *
 * @param      map  The map to calculate the hash value
 * @param      data     The data to find a used hash idx for that contains
 * matched data
 * @param      len      The length of the data
 *
 * @return     Returns the hash value, else -1 if unsuccessful
 */
int find_used_hashval(hashmap_t *map, char *data, size_t len);

/**
 * @brief      Converts the data to an unsigned integer value
 *             Uses a linear probing method for resolving collisions
 *
 * @param      map  The map to calculate the hash value
 * @param      data     The data
 * @param      len      The length of the data
 * @param[in]  max_val  The maximum value
 *
 * @return     Returns the hash value, else -1 if unsuccessful
 */
int find_unused_hashval(hashmap_t *map, char *data, size_t len);

/**
 * @brief      Inserts the given map (key value pair) into the given hashmap
 *
 * @param      map   The map
 * @param      pair  The pair (where 'key' is the buffer and 'value' is the
 * pointer to memory to store)
 * @param      key_len The length of the key
 * @param      val_len The length of the memory at location 'value'
 *
 * @return     Returns the index that the pair was inserted to if success, else
 * -1
 */
int insert_hashmap(hashmap_t *map, map_t *pair, unsigned int key_len,
                   unsigned int val_len);

/**
 * @brief      Removes the given map (key value pair) from the given hashmap
 *
 * @param      map   The map
 * @param      key The key that corresponds to the value to remove from the
 * hashmap
 * @param      key_len The length of the key
 * @param[out]  value The storage for the value deleted from the hashmap
 * @param[out] value_len The length of the value from the found entry
 *
 * @return     Returns 1 that the value was successfully removed from the
 * hashmap, else 0 for not found
 */
int remove_hashmap(hashmap_t *map, void *key, unsigned int key_len,
                   void **value, unsigned int *value_len);

/**
 * @brief      Frees the memory allocated to the given hashmap
 *
 * @param      map   The map
 */
void free_hashmap(hashmap_t *map);

#endif /*HASHMAP_H*/