#include "task.h"
#include "task_pool.h"
#include "test_framework.h"
#include <stdlib.h>

int test_init_task_pool() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    task_pool_t *t_pool = init_task_pool();
    // Make sure everything is initialized
    ASSERT_NOT_NULL(t_pool);
    ASSERT_NOT_NULL(t_pool->t_pool_queue);
    ASSERT_IS_NULL(t_pool->master_thread); // Thread should be initialized by
                                           // init_master_thread, not here

    free_task_pool(t_pool);

    return result;
}

int test_task_pool_get_task() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;

    // Init task pool
    task_pool_t *t_pool = init_task_pool();
    task_t task;
    void *data = NULL;

    // Add a task to the queue and check that it could be obtained
    enqueue(t_pool->t_pool_queue, (void *)&task);
    data = task_pool_get_task(t_pool);
    ASSERT_EQUAL((void *)&task, data);

    // Dequeue again, expecting null
    data = task_pool_get_task(t_pool);
    ASSERT_IS_NULL(data);
    free_task_pool(t_pool);

    return result;
}

/*
 *Runs all task_pool tests
 */
int test_task_pool() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;
    result &= test_init_task_pool();
    result &= test_task_pool_get_task();

    printf((result == SUCCESS) ? "task_pool test SUCCESS\n"
                               : "task_pool test FAIL\n");
    return result;
}