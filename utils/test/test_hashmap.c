#include "hashmap.h"
#include "test_framework.h"
#include <stdlib.h>
#include <string.h>

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

int test_insert_hashmap() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    // Init hashmap
    hashmap_t *test_map = init_hashmap(48);
    int *sizes = malloc(sizeof(int) * 4);
    int idx = 0;

    // Insert one item (collision)
    sizes[0] = 2;
    map_t test1 = {"0", (void *)&sizes[0]};
    map_t test2 = {"00", (void *)&sizes[1]};
    map_t test3 = {"000", (void *)&sizes[2]};
    map_t test4 = {"5", (void *)&sizes[3]};

    idx = insert_hashmap(test_map, &test1);
    printf("num %d\n", idx);
    ASSERT_EQUAL(idx, 0);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(memcmp((char *)test_map->_contents[idx].data, "0", sizes[0]));
    ASSERT_EQUAL(test_map->used, 1);

    // Insert one item (collision)
    sizes[1] = 3;
    idx = insert_hashmap(test_map, &test2);
    printf("num %d\n", idx);
    ASSERT_EQUAL(idx, 1);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(memcmp((char *)test_map->_contents[idx].data, "00", sizes[1]));
    ASSERT_EQUAL(test_map->used, 2);

    // Insert one item (collision)
    sizes[2] = 4;
    idx = insert_hashmap(test_map, &test3);
    printf("num %d\n", idx);
    ASSERT_EQUAL(idx, 2);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(memcmp((char *)test_map->_contents[idx].data, "000", sizes[2]));
    ASSERT_EQUAL(test_map->used, 3);

    // Insert one item (non-collision)
    sizes[3] = 2;
    idx = insert_hashmap(test_map, &test4);
    printf("num %d\n", idx);
    ASSERT_EQUAL(idx, 5);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(memcmp((char *)test_map->_contents[idx].data, "5", sizes[3]));
    ASSERT_EQUAL(test_map->used, 4);

    // Delete entry and test re insert entry replaced
    test_map->_contents[0].is_deleted = 1;
    idx = insert_hashmap(test_map, &test2);
    printf("num %d\n", idx);
    ASSERT_EQUAL(idx, 0);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(memcmp((char *)test_map->_contents[idx].data, "00", sizes[1]));
    ASSERT_EQUAL(test_map->used, 4);

    // Free hashmap
    free_hashmap(test_map);
    test_map = NULL;
    test_map = init_hashmap(4);

    // Test max capacity reached, capacity expanded
    idx = insert_hashmap(test_map, &test1);
    printf("num %d\n", idx);
    ASSERT_EQUAL(idx, 0);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(memcmp((char *)test_map->_contents[idx].data, "0", sizes[0]));
    ASSERT_EQUAL(test_map->used, 1);

    idx = insert_hashmap(test_map, &test2);
    printf("num %d\n", idx);
    ASSERT_EQUAL(idx, 1);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(memcmp((char *)test_map->_contents[idx].data, "00", sizes[1]));
    ASSERT_EQUAL(test_map->used, 2);

    idx = insert_hashmap(test_map, &test3);
    printf("num %d\n", idx);
    ASSERT_EQUAL(idx, 2);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(memcmp((char *)test_map->_contents[idx].data, "000", sizes[2]));
    ASSERT_EQUAL(test_map->used, 3);

    idx = insert_hashmap(test_map, &test4);
    printf("num %d\n", idx);
    ASSERT_EQUAL(idx, 5);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(memcmp((char *)test_map->_contents[idx].data, "5", sizes[3]));
    ASSERT_EQUAL(test_map->used, 4);

    // Make sure capacity doubled
    printf("Capacity: %ld\n", test_map->capacity);
    ASSERT_EQUAL(test_map->capacity, 8);

    // Free hashmap
    free_hashmap(test_map);
    test_map = NULL;
    test_map = init_hashmap(MAX_HASHMAP_SIZE);

    // Simulate Hashmap at least LOAD_CAPACITY full
    unsigned int size = (int)(MAX_HASHMAP_SIZE * MAX_LOAD_CAPACITY);
    printf("Simulated size %u\n", size);

    // Insert one to initialize array
    map_t test_max = {"\n", (void *)&sizes[0]};
    idx = insert_hashmap(test_map, &test_max);
    printf("num %d\n", idx);
    ASSERT_EQUAL(idx, 0);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(memcmp((char *)test_map->_contents[idx].data, "\n", 1));
    ASSERT_EQUAL(test_map->used, 1);

    for (unsigned int ctr = 0; ctr < size; ctr++) {
        test_map->_contents[ctr].data = "test";
        test_map->used++;
    }

    // Try to insert when at max capacity
    printf("Simulated size %u\n", size);
    idx = insert_hashmap(test_map, &test1);
    printf("num %d\n", idx);
    ASSERT_EQUAL(idx, -1);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT_FALSE(memcmp((char *)test_map->_contents[0].data, "\n", 2));
    ASSERT_EQUAL(test_map->used, size);
    ASSERT_EQUAL(test_map->capacity, size)

    return result;
}
int test_hashmap() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    result &= test_init_hashmap();
    result &= test_insert_hashmap();

    printf((result == SUCCESS) ? "Hashmap test SUCCESS\n"
                               : "Hashmap test FAIL\n");
    return result;
}