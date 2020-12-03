#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

/*!
 * @brief	Finds the smallest power of two greater than a given number
 *
 * @param	base The base number
 *
 * @return  The power of two found in the function
 */
static size_t roundup(size_t base) {
    if (base == 0 || base > SIZE_MAX / 2) {
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
 * @param    item_size Size of the items to be stored in the vector in bytes,
 *           must be greater than 0
 *
 * @param    init_size Initial size of vector in number of items
 *
 * @return   A pointer to the new vector, NULL when item_size is zero or memory
 *           allocation fails
 */
vector_t* init_vector_of_size(size_t item_size, size_t init_size) {
    if (item_size == 0) {
        return NULL;
    }

    vector_t* vec = malloc(sizeof(vector_t));

    if (vec == NULL) {
        return NULL;
    }

    vec->item_size = item_size;
    vec->used = 0;
    size_t true_init_size = roundup(init_size);
    vec->capacity = true_init_size;

    /*
     * If they requested 0 bytes, no need to malloc any memory
     * Realloc will act like malloc if the given pointer is null
     */
    if (init_size > 0) {
        vec->_contents = malloc(sizeof(char) * true_init_size * item_size);

        /* Check for memory allocation failure */
        if (vec->_contents == NULL) {
	    free(vec);
            return NULL;
        }
    } else {
        vec->_contents = NULL;
    }

    return vec;
}

/*!
 * @brief     Initializes a new vector of size 0
 *
 * @param     item_size Size of the items to be stored in the vector in bytes,
 *            must be greater than 0
 *
 * @return    A pointer to the new vector, NULL on allocation failure or when
 *            item_size is 0
 */
vector_t* init_vector(size_t item_size) {
    return init_vector_of_size(item_size, 0);
}

/*!
 * @brief	  Extends the vector by a given amount
 *
 * @param[in]     vec Vector to be extended
 *
 * @param         change Amount to grow the vector by
 *
 * @return        Returns 1 on success or 0 on failure
 */
static int extend_vector(vector_t* vec, size_t change) {
    if (vec->used + change <= vec->capacity) {
        return 1;
    }

    size_t n_items = roundup(vec->used + change);
    char* new_buffer = realloc(vec->_contents, n_items * vec->item_size);
    if (new_buffer == NULL) {
        return 0;
    }

    vec->_contents = new_buffer;
    vec->capacity = n_items;
    return 1;
}

/*!
 * @brief      Pushes a single item onto the back of the vector
 *
 * @param[in]  vec Vector to be expanded
 *
 * @param[in]  item Pointer to the item to be deep copied into the vector
 *
 * @return     1 on success, or 0 on failure
 */
int push_vector(vector_t* vec, void* item) {
    if (!extend_vector(vec, 1)) {
        return 0;
    }
    memcpy(&vec->_contents[vec->used * vec->item_size], item, vec->item_size);
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

    return (void*)(&vec->_contents[index * vec->item_size]);
}

/*!
 * @brief     Destroys and frees the memory created by make_vector
 *
 * @param[in] vec Vector to be destroyed
 */
void free_vector(vector_t* vec) {
    if (vec->_contents != NULL)
        free(vec->_contents);

    free(vec);
}

/*!
 * @brief      Returns the byte in the vector at the given index
 *
 * @param[in]  vec Vector to be indexed
 *
 * @param      index Position of the bytes in the contents of the vector
 *
 * @return     A pointer to the bytes, NULL if invalid access
 */
char* index_byte(vector_t* vec, size_t index) {
    if (index >= vec->used)
        return NULL;

    return &vec->_contents[index];
}

/*!
 * @brief      Returns a pointer the to the contents of the vector.  Ownership
 * is maintained by the vector.
 *
 * @param[in]  vec The vector
 *
 * @return     A pointer to the data stored inside the vector
 */
void* get_contents(vector_t* vec) { return (void*)vec->_contents; }
