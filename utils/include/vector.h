/* vector.h */

/*
 * Provides a generic interface to use for a resizeable array
 * The interface is unergonomic and weakly typed, so a type safe
 * wrapper should be created for complex usages
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct {
    size_t capacity;
    size_t used;
    size_t item_bytes;
    char* contents;
} vector_t;

/*
 * Initializes a new vector and returns a pointer to it
 * Takes a number greater than zero as the size of an item in bytes
 * Returns NULL on a failure
 */
vector_t* make_vector(size_t item_bytes);

/*
 * Initializes a new vector of a certain size
 * Same semantics as make_vector
 */
vector_t* make_vector_of_size(size_t item_bytes, size_t init_size);

/*
 * Destroys and frees the memory created by make_vector
 * Completely invalidates all pointers to the vector
 */
void destroy_vector(vector_t* vec);

/*
 * Pushes a single item onto the back of the vector
 * Returns 1 on success, or 0 on failure
 */
int push_vector(vector_t* vec, void* item);

/*
 * Returns a pointer to the item in the vector at the given index
 * Returns NULL if index is invalid
 */
void* index_vector(vector_t* vec, size_t index);

#endif /* VECTOR_H */
