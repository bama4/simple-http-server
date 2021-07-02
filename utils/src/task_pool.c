#include "task_pool.h"
#include "queue.h"
#include "task.h"
#include <semaphore.h>
#include <stdlib.h>

/**
 * @brief      Initializes the task pool. This includes initializing the
 * 			   queue and starting the master_thread that watches the queue for
 * 			   incoming tasks
 *
 * @return     Returns an initialized task_pool or NULL if failed to allocate
 * memory
 */
task_pool_t *init_task_pool(void) {

    task_pool_t *t_pool = NULL;
    queue_t t_pool_queue = NULL;
    // Init queue
    if ((t_pool = calloc(1, sizeof(*t_pool))) == NULL) {
        /*Failed to allocate memory*/
        return NULL;
    }

    if ((t_pool_queue = init_queue()) == NULL) {
        /*Failed to allocate memory*/
        return NULL;
    }

    // Init queue semaphore

    // Init number of tasks

    // Init numer of tasks semaphore

    // Init and start master thread

    return t_pool;
fail:
    // cleanup
}