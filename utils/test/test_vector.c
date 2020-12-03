#include "test_framework.h"
#include "vector.h"

int test_init_vector_of_size() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    // Test empty vector
    vector_t* test_vec = init_vector_of_size(1, 0);
    ASSERT_EQUAL(test_vec->used, 0);
    ASSERT_EQUAL(test_vec->item_size, 1);
    ASSERT_EQUAL(test_vec->capacity, 0);
    ASSERT_IS_NULL(test_vec->_contents);

    // Cleanup
    free_vector(test_vec);

    // Test vector with actual contents
    test_vec = init_vector_of_size(4, 100);
    ASSERT_EQUAL(test_vec->used, 0);
    ASSERT_EQUAL(test_vec->item_size, 4);
    ASSERT_EQUAL(test_vec->capacity, 128);
    ASSERT_NOT_NULL(test_vec->_contents);

    // Cleanup
    free_vector(test_vec);

    // Vector storing zero byte items makes not sense
    test_vec = init_vector_of_size(0, 100);
    ASSERT_IS_NULL(test_vec);

    return result;
}

int test_init_vector() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    // Test initialize vector
    vector_t* test_vec = init_vector(1);
    ASSERT_EQUAL(test_vec->used, 0);
    ASSERT_EQUAL(test_vec->item_size, 1);
    ASSERT_EQUAL(test_vec->capacity, 0);
    ASSERT_IS_NULL(test_vec->_contents);

    free_vector(test_vec);

    // Test invalid item_size
    test_vec = init_vector(0);
    ASSERT_IS_NULL(test_vec);

    return result;
}

int test_push_vector() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    // Test single byte items
    vector_t* vec = init_vector(sizeof(char));
    char c = 'A';

    // Test push one item
    push_vector(vec, (void*)&c);
    ASSERT_EQUAL(vec->used, 1);
    ASSERT_EQUAL(vec->capacity, 1);
    ASSERT_NOT_NULL(vec->_contents);
    ASSERT_EQUAL(vec->_contents[0], c);


    // Test pushing another item
    push_vector(vec, (void*)&c);
    ASSERT_EQUAL(vec->used, 2);
    ASSERT_EQUAL(vec->capacity, 2);
    ASSERT_EQUAL(vec->_contents[1], c);
    free_vector(vec);


    // Test items of size greater than one
    vec = init_vector(sizeof(char*));
    char* words = "BEANS";

    // Push an item
    push_vector(vec, (void*)&words);
    ASSERT_EQUAL(vec->used, 1);
    ASSERT_EQUAL(vec->capacity, 1);
    ASSERT_NOT_NULL(vec->_contents);
    free_vector(vec);

    return result;
}

int test_index_vector() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    // Mock vector, use stack allocated array as the vector doesn't grow
    char contents[] = {1, 0, 0, 0, 2, 0, 0, 0};
    vector_t *vec = init_vector(4);
    vec->_contents = contents;
    vec->used = sizeof(contents);
    vec->capacity = sizeof(contents);

    // Test indexing first item
    int* ret = (int*)index_vector(vec, 0);
    ASSERT_NOT_NULL(ret);
    ASSERT_EQUAL(*ret, 1);
    ASSERT_EQUAL(vec->used, sizeof(contents));
    ASSERT_EQUAL(vec->capacity, sizeof(contents));
    ASSERT_EQUAL(vec->item_size, 4);

    // Test indexing second item
    ret = (int*)index_vector(vec, 1);
    ASSERT_NOT_NULL(ret);
    ASSERT_EQUAL(*ret, 2);
    ASSERT_EQUAL(vec->used, sizeof(contents));
    ASSERT_EQUAL(vec->capacity, sizeof(contents));
    ASSERT_EQUAL(vec->item_size, 4);

    // Test indexing invalid item
    ret = (int*)index_vector(vec, 10);
    ASSERT_IS_NULL(ret);

    return result;
}

int test_vector() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    result &= test_init_vector_of_size();
    result &= test_init_vector();
    result &= test_push_vector();
    result &= test_index_vector();

    printf((result == SUCCESS) ? "Vector test SUCCESS\n"
                               : "Vector test FAIL\n");
    return result;
}
