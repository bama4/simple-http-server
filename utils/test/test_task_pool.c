#include "task.h"
#include "task_pool.h"
#include "test_framework.h"
#include <stdlib.h>

void *task_test_func(void *test_arg) {
    printf("I am a task and my number is %d\n", (int)*(int *)test_arg);

    return NULL;
}

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

    // Create task parameters
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

int test_task_pool_init_master_thread() {
    printf("Running %s\n", __func__);
    int result = SUCCESS;
    int task_1_arg = 1;
    thread_t *master_thread = NULL;

    // Init task pool
    task_pool_t *t_pool = init_task_pool();

    // Create task parameters
    task_t task;
    task.func = task_test_func;
    task.arg = (void *)&task_1_arg;

    // Add a task to the queue and check that it could be obtained
    enqueue(t_pool->t_pool_queue, (void *)&task);

    // Init main task pool thread
    master_thread = task_pool_init_master_thread(t_pool);
    ASSERT_NOT_NULL(master_thread);
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
    result &= test_task_pool_init_master_thread();

    printf((result == SUCCESS) ? "task_pool test SUCCESS\n"
                               : "task_pool test FAIL\n");
    return result;
}