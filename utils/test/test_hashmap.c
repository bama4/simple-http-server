#include "hashmap.h"
#include "test_framework.h"

int test_init_hashmap() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    // Test valid hashmap init
    hashmap_t *test_map = init_hashmap(1);
    ASSERT_NOT_NULL(test_map);
    ASSERT_EQUAL(test_map->capacity, 1);
    ASSERT_EQUAL(test_map->used, 0);
    ASSERT_IS_NULL(test_map->_contents);

    free_hashmap(test_map);
    test_map = NULL;

    // Test invalid hashmap init, size given > MAX_HASHMAP_SIZE
    test_map = init_hashmap(MAX_HASHMAP_SIZE + 1);
    ASSERT_IS_NULL(test_map);

    return result;
}

int test_hashmap() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    result &= test_init_hashmap();

    printf((result == SUCCESS) ? "Hashmap test SUCCESS\n"
                               : "Hashmap test FAIL\n");
    return result;
}