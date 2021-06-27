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
    ASSERT_NOT_NULL(test_map->_contents);

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

    // Insert one item
    sizes[0] = 2;
    sizes[1] = 3;
    sizes[2] = 4;
    sizes[3] = 2;
    map_t test1 = {"0", (void *)&sizes[0]};
    map_t test2 = {"00", (void *)&sizes[1]};
    map_t test3 = {"000", (void *)&sizes[2]};
    map_t test4 = {"5", (void *)&sizes[3]};

    idx = insert_hashmap(test_map, &test1, sizes[0], sizeof(sizes));
    ASSERT_EQUAL(idx, 0);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(test_map->_contents[idx].data == test1.value);
    ASSERT_EQUAL(sizeof(sizes), test_map->_contents[idx].len);
    ASSERT_EQUAL(test_map->used, 1);

    // Insert one item (collision)
    idx = insert_hashmap(test_map, &test2, sizes[1], sizeof(sizes));
    ASSERT_EQUAL(idx, 1);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(test_map->_contents[idx].data == test2.value);
    ASSERT_EQUAL(sizeof(sizes), test_map->_contents[idx].len);
    ASSERT_EQUAL(test_map->used, 2);

    // Insert one item (collision)
    idx = insert_hashmap(test_map, &test3, sizes[2], sizeof(sizes));
    ASSERT_EQUAL(idx, 2);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(test_map->_contents[idx].data == test3.value);
    ASSERT_EQUAL(sizeof(sizes), test_map->_contents[idx].len);
    ASSERT_EQUAL(test_map->used, 3);

    // Insert one item (non-collision)
    idx = insert_hashmap(test_map, &test4, sizes[3], sizeof(sizes));
    ASSERT_EQUAL(idx, 5);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(test_map->_contents[idx].data == test4.value);
    ASSERT_EQUAL(sizeof(sizes), test_map->_contents[idx].len);
    ASSERT_EQUAL(test_map->used, 4);

    // Delete entry and test re insert entry replaced

    // Free hashmap
    free_hashmap(test_map);
    test_map = NULL;

    // Test max capacity reached, capacity expanded
    test_map = init_hashmap(4);

    insert_hashmap(test_map, &test1, sizes[0], sizeof(*sizes));
    insert_hashmap(test_map, &test2, sizes[1], sizeof(*sizes));
    insert_hashmap(test_map, &test3, sizes[2], sizeof(*sizes));
    insert_hashmap(test_map, &test4, sizes[3], sizeof(*sizes));

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
    idx = insert_hashmap(test_map, &test_max, sizes[0], sizeof(sizes));
    ASSERT_EQUAL(idx, 10);
    ASSERT_FALSE(test_map->_contents[idx].is_deleted);
    ASSERT(test_map->_contents[idx].data == &sizes[0]);
    ASSERT_EQUAL(test_map->used, 1);

    for (unsigned int ctr = 0; ctr < size; ctr++) {
        test_map->_contents[ctr].data = "test";
        test_map->used++;
    }

    // Try to insert when at max capacity
    printf("Simulated size %u\n", size);
    idx = insert_hashmap(test_map, &test1, sizes[0], sizeof(*sizes));
    ASSERT_EQUAL(idx, -1);

    free(sizes);
    sizes = NULL;
    free_hashmap(test_map);
    test_map = NULL;
    return result;
}

int test_remove_hashmap() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    // Init hashmap
    hashmap_t *test_map = init_hashmap(48);
    int *sizes = malloc(sizeof(int) * 4);
    int idx = 0;
    void *deleted_value = NULL;
    unsigned int deleted_value_len = 0;
    int removed = 0;

    // Insert one item
    sizes[0] = 2;
    sizes[1] = 3;
    sizes[2] = 4;
    sizes[3] = 2;
    map_t test1 = {"0", (void *)&sizes[0]};
    map_t test2 = {"00", (void *)&sizes[1]};
    map_t test3 = {"000", (void *)&sizes[2]};
    map_t test4 = {"5", (void *)&sizes[3]};

    // Delete using key not in hashmap
    removed = remove_hashmap(test_map, test1.key, sizes[0], &deleted_value,
                             &deleted_value_len);
    ASSERT_FALSE(removed);
    ASSERT_IS_NULL(deleted_value);

    // Delete from NULL hashmap
    removed = remove_hashmap(NULL, test1.key, sizes[0], &deleted_value,
                             &deleted_value_len);
    ASSERT_FALSE(removed);
    ASSERT_IS_NULL(deleted_value);

    // Insert a few items
    int idx_1 = insert_hashmap(test_map, &test1, sizes[0], sizeof(*sizes));
    insert_hashmap(test_map, &test2, sizes[1], sizeof(*sizes));
    insert_hashmap(test_map, &test3, sizes[2], sizeof(*sizes));
    insert_hashmap(test_map, &test4, sizes[3], sizeof(*sizes));
    unsigned int curr_used = test_map->used;

    // Delete the first item
    removed = remove_hashmap(test_map, test1.key, sizes[0], &deleted_value,
                             &deleted_value_len);

    ASSERT(removed);
    ASSERT_EQUAL(test1.value, deleted_value);
    ASSERT_IS_NULL(test_map->_contents[idx_1].data);
    ASSERT_FALSE(test_map->_contents[idx].len);
    ASSERT_EQUAL(test_map->_contents[idx].is_deleted, 1);
    ASSERT_EQUAL(curr_used, test_map->used);
    deleted_value = NULL;
    deleted_value_len = 0;

    // Attempt to delete item that should cause hash collision but is not in the
    // hash table
    removed =
        remove_hashmap(test_map, "`", 2, &deleted_value, &deleted_value_len);
    ASSERT_FALSE(removed);
    ASSERT_IS_NULL(deleted_value);

    // Delete the second item
    removed = remove_hashmap(test_map, test2.key, sizes[1], &deleted_value,
                             &deleted_value_len);

    ASSERT(removed);
    ASSERT_EQUAL(test2.value, deleted_value);
    ASSERT_IS_NULL(test_map->_contents[idx_1].data);
    ASSERT_FALSE(test_map->_contents[idx_1].len);
    ASSERT_EQUAL(test_map->_contents[idx_1].is_deleted, 1);
    ASSERT_EQUAL(curr_used, test_map->used);
    deleted_value = NULL;
    deleted_value_len = 0;

    // Delete the fourth item
    removed = remove_hashmap(test_map, test4.key, sizes[3], &deleted_value,
                             &deleted_value_len);

    ASSERT(removed);
    ASSERT_EQUAL(test4.value, deleted_value);
    ASSERT_IS_NULL(test_map->_contents[idx_1].data);
    ASSERT_FALSE(test_map->_contents[idx_1].len);
    ASSERT_EQUAL(test_map->_contents[idx_1].is_deleted, 1);
    ASSERT_EQUAL(curr_used, test_map->used);
    deleted_value = NULL;
    deleted_value_len = 0;

    free_hashmap(test_map);
    free(sizes);

    return result;
}

int test_hashmap() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    result &= test_init_hashmap();
    result &= test_insert_hashmap();
    result &= test_remove_hashmap();

    printf((result == SUCCESS) ? "Hashmap test SUCCESS\n"
                               : "Hashmap test FAIL\n");
    return result;
}