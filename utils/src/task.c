#include "task.h"
#include "stdlib.h"

/**
 * @brief      Initializes the task.
 *
 * @param      func  The function
 * @param      arg   The argument of the function
 *
 * @return     Returns the initialized task
 */
task_t *init_task(call func, void *arg) {
    task_t *task = NULL;
    if ((task = calloc(1, sizeof(*task))) == NULL) {
        /*Failed to allocate memory*/
        return NULL;
    }
    task->func = func;
    task->arg = arg;
    return task;
}

/**
 * @brief      Frees the given task memory
 *
 * @param      task  The task
 *
 * @return     Returns nothing
 */
void free_task(task_t *task) { free(task); }