#include "queue.h"
#include "test_framework.h"
#include <stdlib.h>

static const char *queue_data[] = {"data1", "data2", "data3"};

int test_init_queue() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    // Test initialize queue
    queue_t *test_queue_t = init_queue();
    ASSERT_NOT_NULL(test_queue_t);

    // Cleanup
    free_queue(test_queue_t);
    test_queue_t = NULL;

    return result;
}

int test_enqueue() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;
    queue_t *test_queue_t = init_queue();

    // Add one item
    enqueue(&test_queue_t, (void *)queue_data[0]);
    ASSERT_EQUAL(get_tail(test_queue_t->_list), (void *)queue_data[0]);
    ASSERT_EQUAL(1, test_queue_t->size);

    // Add another item
    enqueue(&test_queue_t, (void *)queue_data[1]);
    ASSERT_EQUAL(2, test_queue_t->size);
    ASSERT_EQUAL(remove_data(test_queue_t->_list, (void *)queue_data[1]),
                 (void *)queue_data[1])

    // Cleanup
    free_queue(test_queue_t);
    test_queue_t = NULL;

    // Enqueue with NULL ptr
    enqueue(NULL, NULL);
    return result;
}

int test_dequeue() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;
    queue_t *test_queue_t = init_queue();

    // Populate queue
    enqueue(&test_queue_t, (void *)queue_data[0]);
    enqueue(&test_queue_t, (void *)queue_data[1]);
    enqueue(&test_queue_t, (void *)queue_data[2]);

    // Remove one item
    ASSERT_EQUAL(dequeue(test_queue_t), (void *)queue_data[0])
    ASSERT_EQUAL(2, test_queue_t->size);

    // Remove another item
    ASSERT_EQUAL(dequeue(test_queue_t), (void *)queue_data[1])
    ASSERT_EQUAL(1, test_queue_t->size);

    // Remove another item
    ASSERT_EQUAL(dequeue(test_queue_t), (void *)queue_data[2])
    ASSERT_EQUAL(0, test_queue_t->size);

    // Dequeue from empty queue
    ASSERT_IS_NULL(dequeue(test_queue_t));
    ASSERT_EQUAL(0, test_queue_t->size);

    // Cleanup
    free_queue(test_queue_t);
    test_queue_t = NULL;

    // Dequeue with NULL ptr
    ASSERT_IS_NULL(dequeue(NULL));
    return result;
}

int test_front() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;
    queue_t *test_queue_t = init_queue();

    // Populate queue
    enqueue(&test_queue_t, (void *)queue_data[0]);
    enqueue(&test_queue_t, (void *)queue_data[1]);
    enqueue(&test_queue_t, (void *)queue_data[2]);

    // Test front
    ASSERT_EQUAL(front(test_queue_t), (void *)queue_data[0]);
    dequeue(test_queue_t);

    // Test front 2nd time
    ASSERT_EQUAL(front(test_queue_t), (void *)queue_data[1]);
    dequeue(test_queue_t);

    // Test front 3rd time
    ASSERT_EQUAL(front(test_queue_t), (void *)queue_data[2]);
    dequeue(test_queue_t);

    // Test front on empty queue
    ASSERT_IS_NULL(front(test_queue_t));

    // Cleanup
    free_queue(test_queue_t);
    test_queue_t = NULL;

    // Front with NULL ptr
    ASSERT_IS_NULL(front(NULL));
    return result;
}

int test_free_queue() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;
    queue_t *test_queue_t = init_queue();

    // Populate queue
    enqueue(&test_queue_t, (void *)queue_data[0]);

    // Test queue deleted
    free_queue(test_queue_t);
    test_queue_t = NULL;
    ASSERT_IS_NULL(test_queue_t);

    // Test free NULL ptr
    free_queue(NULL);

    return result;
}

/*
 *Runs all queue tests
 */
int test_queue() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;
    result &= test_init_queue();
    result &= test_enqueue();
    result &= test_dequeue();
    result &= test_front();
    result &= test_free_queue();

    printf((result == SUCCESS) ? "Queue test SUCCESS\n" : "Queue test FAIL\n");
    return result;
}