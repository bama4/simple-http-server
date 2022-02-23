/*
This file defines an API for a task pool. A task pool is a
queue of tasks with a master thread assigned to

 */
#include "task_pool.h"
#include "queue.h"
#include "task.h"
#include "utils.h"
#include <assert.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

#define MAIN_TASK_LOOP_VAL 0
#ifdef DEBUG
#define MAIN_TASK_LOOP_VAL 1
#endif

/**
 * @brief      Initializes the task pool. This includes initializing the
 * 			   queue and starting the master_thread that watches the queue for
 * 			   incoming tasks
 *
 * @return     Returns an initialized task_pool or NULL if failed to allocate
 * memory
 */
task_pool_t *init_task_pool() {
    task_pool_t *t_pool = NULL;
    queue_t *t_pool_queue = NULL;

    // Init queue
    if ((t_pool = calloc(1, sizeof(*t_pool))) == NULL) {
        /*Failed to allocate memory*/
        goto fail;
    }

    if ((t_pool_queue = init_queue()) == NULL) {
        /*Failed to allocate memory*/
        goto fail;
    }
    t_pool->t_pool_queue = t_pool_queue;

    // Init queue semaphore
    if (sem_init(&t_pool->t_pool_queue_sem, 0, 1) < 0) {
        /*Failed to set t pool sem*/
        goto fail;
    }

    t_pool->master_thread = NULL;

    return t_pool;
fail:
    // Cleanup
    free_task_pool(t_pool);
    return NULL;
}

/**
 * @brief      Initializes the master thread.
 *
 * @param      t_pool  The t pool
 *
 * @return     Returns the thread object
 */
thread_t *task_pool_init_master_thread(task_pool_t *t_pool) {
    assert(t_pool);

    // Init and start master thread
    if ((t_pool->master_thread = calloc(1, sizeof(*t_pool->master_thread))) ==
        NULL) {
        /*Failed to allocate memory*/
        goto fail;
    }

    t_pool->master_thread->t_pool = t_pool;
    t_pool->master_thread->task.func = &task_pool_master_task;
    t_pool->master_thread->task.arg = (void *)t_pool;
    if (pthread_create(&t_pool->master_thread->thread_id, NULL,
                       *(t_pool->master_thread->task.func),
                       t_pool->master_thread->task.arg) < 0) {
        /*Error creating thread*/
        goto fail;
    }
    pthread_join(t_pool->master_thread->thread_id, NULL);
    DEBUG_PRINT("Master thread attempting to take from queue\n")
    // t_pool->master_thread->thread_id);

    return t_pool->master_thread;
fail:
    // Cleanup
    free(t_pool->master_thread);
    return NULL;
}

/**
 * @brief      Dequeues a task from the t_pool queue
 *
 * @param      t_pool  The t pool
 *
 * @return     returns the data dequeued
 */
void *task_pool_get_task(task_pool_t *t_pool) {
    assert(t_pool); // assert not NULL

    DEBUG_PRINT("attempting to take queue\n");
    sem_trywait(&t_pool->t_pool_queue_sem);
    void *task = dequeue(t_pool->t_pool_queue);
    sem_post(&t_pool->t_pool_queue_sem);

    return task;
}

/**
 * @brief      The main task of the thread pool master.
 *             The master thread is initialized with an execute task function
 *             that dequeues the next task from the task_pool_queue and executes
 * 			   it as a new thread
 *
 * @return     Returns the thread_t ptr to the master thread
 */
void *task_pool_master_task(void *t_pool) {
    assert(t_pool); // assert not NULL
    task_t *task = NULL;
    thread_t thread;

    /*loop on queue forever if not in debug mode*/
    do {
        sleep(1);
        DEBUG_PRINT("Master thread attempting to take from queue\n");
        task = (task_t *)task_pool_get_task(t_pool);
        thread.t_pool = t_pool;
        thread.task = *task;

        if (task) {
            DEBUG_PRINT("Found a task in the queue, executing\n");
            /* Execute thread */
            if (pthread_create(&thread.thread_id, NULL, *(thread.task.func),
                               thread.task.arg) < 0) {
                /*Error creating thread*/
                goto fail;
            }
            DEBUG_PRINT("Executing task with ID \n");
        }
    } while (MAIN_TASK_LOOP_VAL);

fail:
    return NULL;
}

/**
 * @brief      Frees the task_pool and stops the master thread
 *
 * @param      t_pool  The t pool
 */
void free_task_pool(task_pool_t *t_pool) {
    // Cleanup
    if (t_pool != NULL) {
        // Cleanup thread_t
        if (t_pool->master_thread != NULL) {
            free(t_pool->master_thread);
            t_pool->master_thread = NULL;
        }

        // Cleanup queue_t
        if (t_pool->t_pool_queue != NULL) {
            free_queue(t_pool->t_pool_queue);
            t_pool->t_pool_queue = NULL;
        }
        free(t_pool);
    }
}