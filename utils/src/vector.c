/* vector.c */

#include "vector.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/* Rounds a number up to the nearest power of 2 */
static size_t roundup(size_t base) {
    if (base <= 0 || base >= (size_t)-1) {
        return 0;
    }

    size_t acc = 1;
    while (base > acc) {
        acc *= 2;
    }
    return acc;
}

vector_t* make_vector_of_size(size_t item_bytes, size_t init_size) {
    /* Makes no sense for the item_bytes to be 0 */
    assert(item_bytes != 0);

    vector_t* vec = malloc(sizeof(vector_t));

    vec->item_bytes = item_bytes;
    vec->used = 0;
    size_t true_init_size = roundup(init_size);
    vec->capacity = true_init_size;

    /* If they requests 0 bytes, no need to malloc any memory */
    if (init_size > 0) {
        vec->contents = malloc(sizeof(char) * true_init_size * item_bytes);

        /* Check for memory allocation failure */
        if (vec->contents == NULL) {
            return NULL;
        }
    } else {
        vec->contents = NULL;
    }

    return vec;
}

vector_t* make_vector(size_t item_bytes) {
    return make_vector_of_size(item_bytes, 0);
}

void destroy_vector(vector_t* vec) {
    if (vec->capacity > 0)
        free(vec->contents);

    free(vec);
}

/* Extends the vector by a given amount */
static int extend_vector(vector_t* vec, size_t change) {
    if (vec->used + change <= vec->capacity) {
        return 1;
    }

    size_t n_items = roundup(vec->used + change);
    char* new_buffer = realloc(vec->contents, n_items * vec->item_bytes);
    if (new_buffer == NULL) {
        return 0;
    }

    vec->contents = new_buffer;
    vec->capacity = n_items;
    return 1;
}

int push_vector(vector_t* vec, void* item) {
    if (extend_vector(vec, 1) == 0) {
        return 0;
    }
    memcpy(&vec->contents[vec->used * vec->item_bytes], item, vec->item_bytes);
    vec->used += 1;
    return 1;
}

/*
 * Returns a pointer to the item in the vector at the given index
 * Returns NULL if index is invalid
 */
void* index_vector(vector_t* vec, size_t index) {
    if (index >= vec->used)
        return NULL;

    return (void*)&vec->contents[index * vec->item_bytes];
}
