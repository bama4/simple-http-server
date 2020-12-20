#include "hashmap.h"
#include <stdlib.h>
#include <string.h>

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
 * @brief      Converts the data to an unsigned integer value
 *
 * @param      map  The map to calculate the hash value
 * @param      data     The data
 * @param      len      The length of the data
 *
 * @return     Returns the hash value, else -1 if unsuccessful
 */
int hashval(hashmap *map, char *data, size_t len) {
    if (data == NULL) {
        return -1;
    }
    int value = 0;
    for (int ctr = 0; ctr < len; ctr++) {
        value += (int)(data[ctr]);
    }
    value = value % map->capacity;

    while (map->_contents[value].data != NULL ||
           map->_contents[value].is_deleted == 0) {
        value = 0;

        // Check for collision
        if (map->)
    }
    return value;
}

/**
 * @brief      Inserts the given map (key value pair) into the given hashmap
 *
 * @param      map   The map
 * @param      pair  The pair
 *
 * @return     Returns the index that the pair was inserted to if success, else
 * -1
 */
int insert_hashmap(hashmap_t *map, map_t *pair) {
    if (map == NULL || pair == NULL) {
        return -1;
    }

    // Check if first insertion
    if (map->_contents == NULL) {
        // initialize _contents
        map->_contents = (entry_t *)calloc(map->capacity, sizeof(entry_t));

        // Check if used / capacity >= MAX_LOAD_CAPACITY
    } else if ((map->used / (map->capacity * 1.0)) >= MAX_LOAD_CAPACITY) {
        // Time to increase the capacity

        // Check that the new capacity won't exceed MAX_HASHMAP_SIZE
        size_t new_size = 0;
        if (map->capacity == MAX_HASHMAP_SIZE) {
            // map already at MAX_HASHMAP_SIZE
            return -1;
        } else if (map->capacity * 2 <= MAX_HASHMAP_SIZE) {
            // Only increase capacity to the MAX_HASHMAP_SIZE
            new_size = map->capacity * 2;
        } else {
            // Allocate what is left
            new_size = map->capacity + (MAX_HASHMAP_SIZE - map->capacity);
        }

        entry_t *old_contents = map->_contents;
        entry_t *new_contents = (entry_t *)calloc(new_size, sizeof(entry_t));
        // copy memory contents to newly allocated memory
        entry_t *dst = memcpy(new_contents, old_contents, map->used);

        if (dst == NULL) {
            // Failed to increase the capacity, calloc failed
            return -1;
        }
        // Free old contents buffer
        free(map->_contents);
        map->_contents = NULL;

        map->_contents = new_contents;
    }

    // insert item
    size_t idx = 0;

    idx = hashval(map, pair->key);
    if (idx == -1) {
        // There is an issue with the data
        return -1;
    }

    map->_contents[idx].data = pair->value;
    return idx;
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