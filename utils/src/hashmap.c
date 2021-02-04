#include "hashmap.h"
#include <errno.h>
#include <stdio.h>
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
 * the map
 *
 * @param      map  The map to calculate the hash value
 * @param      data     The data
 * @param      len      The length of the data
 *
 * @return     Returns the hash value, else -1 if unsuccessful
 */
int hashval(hashmap_t *map, char *data, size_t len) {
    if (data == NULL) {
        return -1;
    }
    int value = 0;
    for (unsigned int ctr = 0; ctr < len; ctr++) {
        value += (char)(data[ctr]);
    }

    value = value % map->capacity;
    unsigned int iter_count = 0;

    // Keep iterating until there is a free or deleted space
    printf("Before loop %d\n", value);
    while (map->_contents[value].data != NULL &&
           map->_contents[value].is_deleted != 1) {
        printf("%d\n", value);
        // There is a collision, recalculate value
        value = (value + 1) % map->capacity;
        iter_count += 1;

        // No place found
        // This case should not be reached if capacity is limited
        if (iter_count == map->capacity) {
            value = -1;
            break;
        }
    }
    return value;
}

/**
 * @brief      Inserts the given map (key value pair) into the given hashmap
 *
 * @param      map   The map
 * @param      pair  The pair (where 'key' is the buffer and 'value' is the
 * length)
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
        if ((map->_contents = calloc(map->capacity, sizeof(entry_t))) == NULL) {
            return -1;
        }

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
        entry_t *new_contents = NULL;
        if ((new_contents = calloc(new_size, sizeof(entry_t))) == NULL) {
            return -1;
        }

        // Copy memory contents to newly allocated memory
        entry_t *dst = memcpy(new_contents, old_contents, map->used);

        if (dst == NULL) {
            // Failed to increase the capacity, memcpy failed
            return -1;
        }
        // Free old contents buffer
        free(map->_contents);
        map->_contents = NULL;

        map->_contents = new_contents;
        map->capacity = new_size;
    }
    int idx = 0;
    // Calculate hash value for item, treats value as length
    int len = *((int *)pair->value);
    idx = hashval(map, pair->key, len);
    if (idx == -1) {
        // There is an issue with inserting the data
        return -1;
    }

    // Only count new space taken as additional used
    if (!map->_contents[idx].is_deleted) {
        map->used += 1;
    }

    map->_contents[idx].data = pair->value;
    map->_contents[idx].is_deleted = 0;
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