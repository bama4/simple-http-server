#include "test_framework.h"
#include "vector.h"

typedef int (*test_func_sig)();

int test_init_vector_of_size() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    vector_t* test_vec = init_vector_of_size(1, 0);
    ASSERT(test_vec->used == 0);
    ASSERT(test_vec->item_size == 1);
    ASSERT(test_vec->capacity == 0);
    ASSERT(test_vec->contents == NULL);

    free_vector(test_vec);
    test_vec = init_vector_of_size(4, 100);
    ASSERT(test_vec->used == 0);
    ASSERT(test_vec->item_size == 4);
    ASSERT(test_vec->capacity == 128);
    ASSERT(test_vec->contents != NULL);

    free_vector(test_vec);
    test_vec = init_vector_of_size(0, 100);
    ASSERT(test_vec == NULL);

    return result;
}

int test_init_vector() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    vector_t* test_vec = init_vector(1);
    ASSERT(test_vec->used == 0);
    ASSERT(test_vec->item_size == 1);
    ASSERT(test_vec->capacity == 0);
    ASSERT(test_vec->contents == NULL);

    free_vector(test_vec);
    test_vec = init_vector(0);
    ASSERT(test_vec == NULL);

    return result;
}

int test_push_vector() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    vector_t* vec = init_vector(sizeof(char));

    char c = 'A';
    char* words = "BEANS";

    push_vector(vec, (void*)&c);

    ASSERT_EQUAL(vec->used, 1);
    ASSERT_EQUAL(vec->capacity, 1);
    ASSERT_NOT_NULL(vec->contents);
    ASSERT_EQUAL(vec->contents[0], c);

    push_vector(vec, (void*)&c);

    ASSERT_EQUAL(vec->used, 2);
    ASSERT_EQUAL(vec->capacity, 2);
    ASSERT_EQUAL(vec->contents[1], c);

    free_vector(vec);
    vec = init_vector(sizeof(char*));

    push_vector(vec, (void*)&words);

    ASSERT_EQUAL(vec->used, 1);
    ASSERT_EQUAL(vec->capacity, 1);
    ASSERT_NOT_NULL(vec->contents);

    free_vector(vec);
    return result;
}

int test_index_vector() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    char contents[] = {1, 0, 0, 0, 2, 0, 0, 0};
    vector_t vec = {
        .contents = (void*)contents, .used = 2, .capacity = 2, .item_size = 4};

    int* ret = (int*)index_vector(&vec, 0);
    ASSERT_NOT_NULL(ret);
    ASSERT_EQUAL(*ret, 1);

    ret = (int*)index_vector(&vec, 1);
    ASSERT_NOT_NULL(ret);
    ASSERT_EQUAL(*ret, 2);

    ret = (int*)index_vector(&vec, 10);
    ASSERT_IS_NULL(ret);

    return result;
}

int test_vector() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    result += test_init_vector_of_size();
    result += test_init_vector();
    result += test_push_vector();
    result += test_index_vector();

    printf((result == SUCCESS) ? "Vector test SUCCESS\n"
                               : "Vector test FAIL\n");
    return result;
}
