#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct {
    size_t capacity;
    size_t used;
    size_t item_bytes;
    char* contents;
} vector_t;

/*!
 * @brief    Initializes a new vector of size 0
 *
 * @param    item_size Size of the items to be stored in the vector in bytes
 *
 * @return   A pointer to the new vector
 */
vector_t* init_vector(size_t item_size);

/*!
 * @brief    Initializes a new vector of a certain size
 *
 * @param    item_size Size of the items to be stored in the vector in bytes
 *
 * @param    init_size Initial size of vector in number of items
 *
 * @return   A pointer to the new vector
 */
vector_t* init_vector_of_size(size_t item_size, size_t init_size);

/*!
 * @brief     Destroys and frees the memory created by make_vector
 *
 * @param[in] vec Vector to be destroyed
 */
void free_vector(vector_t* vec);

/*!
 * @brief     Pushes a single item onto the back of the vector
 *
 * @param[in] vec Vector to be expanded
 *
 * @param[in] item Pointer to item to be deep copied into the vector
 *
 * @return     1 on success, or 0 on failure
 */
int push_vector(vector_t* vec, void* item);

/*!
 * @brief      Indexes the vector and returns a pointer to the item
 *
 * @param[in]  vec Vector to be indexed
 *
 * @param      index Position of the item in the vector
 *
 * @return     A pointer to the item, NULL if index is invalid
 */
void* index_vector(vector_t* vec, size_t index);

#endif /* VECTOR_H */
