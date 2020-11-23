#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

/*!
 * @brief	Finds the smallest power of two greater than a number
 *
 * @param	base The base number
 *
 * @return  The power of two found in the function
 */
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

/*!
 * @brief    Initializes a new vector of a certain size
 *
 * @param    item_size Size of the items to be stored in the vector in bytes
 *
 * @param    init_size Initial size of vector in number of items
 *
 * @return   A pointer to the new vector
 */
vector_t* init_vector_of_size(size_t item_bytes, size_t init_size) {
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

/*!
 * @brief     Initializes a new vector of size 0
 *
 * @param     item_size Size of the items to be stored in the vector in bytes
 *
 * @return    A pointer to the new vector
 */
vector_t* init_vector(size_t item_bytes) {
    return make_vector_of_size(item_bytes, 0);
}

/*!
 * @brief     Destroys and frees the memory created by make_vector
 *
 * @param[in] vec Vector to be destroyed
 */
void free_vector(vector_t* vec) {
    if (vec->capacity > 0)
        free(vec->contents);

    free(vec);
}

/*!
 * @brief	  Extends the vector by a given amount
 *
 * @param[in] vec Vector to be extended
 *
 * @param     change Amount to grow the vector by
 */
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

/*!
 * @brief     Pushes a single item onto the back of the vector
 *
 * @param[in] vec Vector to be expanded
 *
 * @param[in] item Pointer to item to be deep copied into the vector
 *
 * @return     1 on success, or 0 on failure
 */
int push_vector(vector_t* vec, void* item) {
    if (extend_vector(vec, 1) == 0) {
        return 0;
    }
    memcpy(&vec->contents[vec->used * vec->item_bytes], item, vec->item_bytes);
    vec->used += 1;
    return 1;
}

/*!
 * @brief      Indexes the vector and returns a pointer to the item
 *
 * @param[in]  vec Vector to be indexed
 *
 * @param      index Position of the item in the vector
 *
 * @return     A pointer to the item, NULL if index is invalid
 */
void* index_vector(vector_t* vec, size_t index) {
    if (index >= vec->used)
        return NULL;

    return (void*)&vec->contents[index * vec->item_bytes];
}
