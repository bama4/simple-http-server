#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct {
    size_t capacity;
    size_t used;
    size_t item_size;
    char* _contents;
} vector_t;

/*!
 * @brief     Initializes a new vector of size 0
 *
 * @param     item_size Size of the items to be stored in the vector in bytes,
 *            must be greater than 0
 *
 * @return    A pointer to the new vector, NULL on allocation failure or when
 *            item_size is 0
 */
vector_t* init_vector(size_t item_size);

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
vector_t* init_vector_of_size(size_t item_size, size_t init_size);

/*!
 * @brief      Pushes a single item onto the back of the vector
 *
 * @param[in]  vec Vector to be expanded
 *
 * @param[in]  item Pointer to the item to be deep copied into the vector
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

/*!
 * @brief      Returns the byte in the vector at the given index
 *
 * @param[in]  vec Vector to be indexed
 *
 * @param[out] byte The value of the index
 *
 * @param      index Position of the bytes in the contents of the vector
 *
 * @return     1 on success, 0 on failure
 */
int index_byte(vector_t* vec, char* byte, size_t index);

/*!
 * @brief      Returns a pointer the to the contents of the vector.  Ownership
 * is maintained by the vector.
 *
 * @param[in]  vec The vector
 *
 * @return     A pointer to the data stored inside the vector
 */
void* get_contents(vector_t* vec);

/*!
 * @brief     Destroys and frees the memory created by make_vector
 *
 * @param[in] vec Vector to be destroyed
 */
void free_vector(vector_t* vec);
#endif /* VECTOR_H */
