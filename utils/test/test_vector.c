/* test_vector.c */

#include <stdint.h>
#include <stdio.h>

#include "test_framework.h"
#include "vector.c"

typedef int (*test_func_sig)(void);

int test_roundup() {
    ASSERT(roundup(0) == 0);
    ASSERT(roundup(2) == 2);
    ASSERT(roundup(3) == 4);
    ASSERT(roundup(10) == 16);
    ASSERT(roundup(65) == 128);

    ASSERT(roundup(SIZE_MAX) == 0);

    return SUCCESS;
}

int test_make_vector_of_size() {
    vector_t* test_vec = make_vector_of_size(1, 0);
    ASSERT(test_vec->used == 0);
    ASSERT(test_vec->item_bytes == 1);
    ASSERT(test_vec->capacity == 0);
    ASSERT(test_vec->contents == NULL);

    test_vec = make_vector_of_size(4, 100);
    ASSERT(test_vec->used == 0);
    ASSERT(test_vec->item_bytes == 4);
    ASSERT(test_vec->capacity == 128);
    ASSERT(test_vec->contents != NULL);

    return SUCCESS;
}

int test_make_vector() {
    vector_t* test_vec = make_vector(1);
    ASSERT(test_vec->used == 0);
    ASSERT(test_vec->item_bytes == 1);
    ASSERT(test_vec->capacity == 0);
    ASSERT(test_vec->contents == NULL);

    return SUCCESS;
}

int test_push_vector() {
    vector_t vec = {
        .contents = NULL, .used = 0, .capacity = 0, .item_bytes = 1};

    char c = 'A';

    push_vector(&vec, (void*)&c);

    ASSERT(vec.used == 1);
    ASSERT(vec.capacity == 1);
    ASSERT(vec.contents != NULL);
    ASSERT(vec.contents[0] == c);

    push_vector(&vec, (void*)&c);

    ASSERT(vec.used == 2);
    ASSERT(vec.capacity == 2);
    ASSERT(vec.contents[1] == c);

    return SUCCESS;
}

int test_index_vector() {
    char contents[] = {1, 0, 0, 0, 2, 0, 0, 0};
    vector_t vec = {
        .contents = (void*)contents, .used = 2, .capacity = 2, .item_bytes = 4};

    int* ret = (int*)index_vector(&vec, 0);
    ASSERT(ret != NULL);
    ASSERT(*ret == 1);

    ret = (int*)index_vector(&vec, 1);
    ASSERT(ret != NULL);
    ASSERT(*ret == 2);

    ret = (int*)index_vector(&vec, 10);
    ASSERT(ret == NULL);
    return SUCCESS;
}

test_func_sig functions[] = {test_roundup, test_make_vector_of_size,
                             test_make_vector, test_push_vector,
                             test_index_vector};

int main() {
    for (long unsigned int i = 0; i < sizeof(functions) / 8; i++) {
        test_func_sig temp = functions[i];
        int result = temp();
        if (result == -1) {
            printf("TEST %ld: SUCCESS\n", i + 1);
        } else {
            printf("TEST %ld: FAIL on line: %d\n", i + 1, result);
        }
    }
}
