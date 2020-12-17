#include "linked_list.h"
#include "test_framework.h"
#include <stdlib.h>

static const char *linked_list_data[] = {"data1", "data2", "data3"};

int test_init_list() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    // Test init_list
    linked_list_t *test_list = init_list();
    ASSERT_NOT_NULL(test_list);

    // Cleanup
    free_list(test_list);
    test_list = NULL;
    return result;
}

int test_get_tail() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;
    linked_list_t *test_list = init_list();

    // Test tail updated on first insert
    insert_data(test_list, (void *)linked_list_data[0]);
    ASSERT_EQUAL(test_list->head, test_list->tail);
    ASSERT_EQUAL(test_list->tail->data, get_tail(test_list));

    // Test tail the same on second insert
    insert_data(test_list, (void *)linked_list_data[1]);
    ASSERT_NOT_EQUAL(test_list->head, test_list->tail);
    ASSERT_EQUAL(test_list->tail->data, get_tail(test_list));

    // Test tail updated on removal of item
    insert_data(test_list, (void *)linked_list_data[2]);
    remove_data(test_list, (void *)linked_list_data[0]);
    ASSERT_EQUAL(test_list->tail->data, (void *)linked_list_data[1]);
    ASSERT_EQUAL(test_list->tail->data, get_tail(test_list));

    // Cleanup
    free_list(test_list);
    test_list = NULL;

    // Get_tail with NULL ptr
    ASSERT_IS_NULL(get_tail(NULL));
    return result;
}

int test_insert_data() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;
    linked_list_t *test_list = init_list();

    // Test insert at empty head
    insert_data(test_list, (void *)linked_list_data[0]);
    ASSERT_NOT_NULL(test_list->head);
    ASSERT_EQUAL(test_list->head->data, (void *)linked_list_data[0]);
    ASSERT_EQUAL(test_list->head, test_list->tail);

    // Test insert at non-empty head
    insert_data(test_list, (void *)linked_list_data[1]);
    ASSERT_NOT_NULL(test_list->head);
    ASSERT_NOT_NULL(test_list->head->next);
    ASSERT_EQUAL(test_list->head->data, (void *)linked_list_data[1]);
    ASSERT_EQUAL(test_list->head->next->data, (void *)linked_list_data[0]);

    // Test insert with more than one item in list
    insert_data(test_list, (void *)linked_list_data[2]);
    ASSERT_NOT_NULL(test_list->head);
    ASSERT_NOT_NULL(test_list->head->next->next);
    ASSERT_EQUAL(test_list->head->data, (void *)linked_list_data[2]);
    ASSERT_EQUAL(test_list->head->next->next->data,
                 (void *)linked_list_data[0]);

    // Cleanup
    free_list(test_list);
    test_list = NULL;

    // Insert_data with NULL ptr
    ASSERT_IS_NULL(insert_data(NULL, NULL));
    return result;
}

int test_remove_data() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;
    void *removed_data = NULL;
    linked_list_t *test_list = init_list();

    // Populate list
    insert_data(test_list, (void *)linked_list_data[0]);
    insert_data(test_list, (void *)linked_list_data[1]);
    insert_data(test_list, (void *)linked_list_data[2]);

    // Test remove head
    ASSERT_EQUAL(test_list->head->data, (void *)linked_list_data[2]);
    removed_data = remove_data(test_list, (void *)linked_list_data[2]);
    ASSERT_EQUAL(test_list->head->data, (void *)linked_list_data[1]);
    ASSERT_EQUAL(removed_data, (void *)linked_list_data[2]);
    ASSERT_IS_NULL(remove_data(test_list, (void *)linked_list_data[2]));

    // Test remove non-head
    removed_data = remove_data(test_list, (void *)linked_list_data[0]);
    ASSERT_EQUAL(removed_data, (void *)linked_list_data[0]);
    ASSERT_IS_NULL(remove_data(test_list, (void *)linked_list_data[0]));

    // Cleanup
    free_list(test_list);
    test_list = NULL;

    // Remove_data with NULL ptr
    ASSERT_IS_NULL(remove_data(NULL, NULL));
    return result;
}

int test_remove_tail() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;
    void *removed_data = NULL;
    linked_list_t *test_list = init_list();

    // Populate list
    insert_data(test_list, (void *)linked_list_data[0]);
    insert_data(test_list, (void *)linked_list_data[1]);
    insert_data(test_list, (void *)linked_list_data[2]);

    // Test tail data removed and returned
    removed_data = remove_tail(test_list);
    ASSERT_EQUAL(removed_data, (void *)linked_list_data[0]);
    ASSERT_IS_NULL(remove_data(test_list, (void *)linked_list_data[0]));

    // Cleanup
    free_list(test_list);
    test_list = NULL;

    // Remove_tail with NULL ptr
    ASSERT_IS_NULL(remove_tail(NULL));
    return result;
}

int test_free_list() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;
    linked_list_t *test_list = init_list();

    // Populate list
    insert_data(test_list, (void *)linked_list_data[0]);
    insert_data(test_list, (void *)linked_list_data[1]);
    insert_data(test_list, (void *)linked_list_data[2]);

    // Test list NULL
    free_list(test_list);
    test_list = NULL;
    ASSERT_IS_NULL(test_list);

    // Free_list with NULL ptr no error
    free_list(NULL);
    return result;
}

/*
 *Runs all linked list tests
 */
int test_linked_list() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;
    result &= test_init_list();
    result &= test_get_tail();
    result &= test_insert_data();
    result &= test_remove_data();
    result &= test_remove_tail();
    result &= test_free_list();

    printf((result == SUCCESS) ? "Linked list test SUCCESS\n"
                               : "Linked list test FAIL\n");
    return result;
}