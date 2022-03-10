#include "task.h"
#include "stdlib.h"
#include "utils.h" /* ProgramState */
#include <assert.h>

/**
 * @brief      Initializes the task.
 *
 * @param      func  The function
 * @param      arg   The argument of the function
 *
 * @return     Returns the initialized task
 */
task_t *init_task(call func, void *arg) {
    assert(arg);
    task_t *task = NULL;

    if ((task = calloc(1, sizeof(*task))) == NULL) {
        /*Failed to allocate memory*/
        return NULL;
    }
    init_task_values(task, func, arg);
    return task;
}

/**
 * @brief      Initializes the task values.
 *
 * @param      task  The task to set the values for
 * @param      func  The function
 * @param      arg   The argument of the function
 *
 * @return     Returns the initialized task
 */
void init_task_values(task_t *task, call func, void *arg) {
    assert(task);
    assert(arg);
    task->func = func;
    task->arg.pre_task_callback = &pre_task_callback;
    task->arg.post_task_callback = &post_task_callback;
    task->arg.arg = arg;
}

/**
 * @brief    Called before each tasks callback when spun off as a thread
 */
void pre_task_callback() { ProgramState.total_num_threads++; }

/**
 * @brief    Called after each tasks callback when spun off as a thread
 */
void post_task_callback() { ProgramState.total_num_threads--; }

/**
 * @brief      Frees the given task memory
 *
 * @param      task  The task
 *
 * @return     Returns nothing
 */
void free_task(task_t *task) { free(task); }