#ifndef TASKPOOL_H_
#define TASKPOOL_H_
#include "queue.h"
#include "task.h"
#include <pthread.h>
#include <semaphore.h>

#define MAX_TASKPOOL_SIZE 5

typedef void (*call)(void *in);

typedef struct _task_pool task_pool_t;

typedef struct {
    pthread_t thread_id; /*The posix thread id*/
    task_t task;         /*The task that the thread is running*/
    task_pool_t *t_pool; /*The thread pool that the task is associated with*/
} thread_t;

struct _task_pool {
    queue_t *t_pool_queue;  /*a queue of tasks */
    unsigned int num_tasks; /*number of tasks currently in the queue*/
    sem_t *num_tasks_sem;
    sem_t *t_pool_queue_sem;
    thread_t *master_thread; /*a master thread that is responsible for executing
                              tasks in the queue*/
};

/**
 * @brief      Initializes the task pool. This includes initializing the
 * 			   queue and starting the master_thread that watches the queue for
 * 			   incoming tasks
 *
 * @return     Returns an initialized task_pool
 */
task_pool_t *init_task_pool(void);

/**
 * @brief      Adds (enqueues) a task to the task_pool
 *
 * @param      t_pool  The task pool
 * @param      task    The task to add to the task pool
 *
 * @return     Returns the task added, else returns NULL
 */
void *task_pool_add(task_pool_t *t_pool, task_t *task);

/**
 * @brief      Initializes the task pool master.
 *             The master thread is initialized with a execute task function
 *             that dequeues the next task from the task_pool_queue and executes
 * 			   it as a new thread
 *
 * @return     Returns the thread_t ptr to the master thread
 */
thread_t *init_task_pool_master(void);

/**
 * @brief      Starts a new thread with the given task
 *
 * @param      task  The task
 *
 * @return     returns the thread created from executing the task
 */
thread_t *execute_task(task_t *task);

/**
 * @brief      Frees the task_pool and stops the master thread
 *
 * @param      t_pool  The t pool
 */
void free_task_pool(task_pool_t *t_pool);

#endif /*TASKPOOL_H_*/
