#ifndef TASK_H_
#define TASK_H_

typedef void *(*call)(void *arg);

typedef struct {

    call func; /*function to be called*/
    void *arg; /*function arguments*/
} task_t;

/**
 * @brief      Initializes the task.
 *
 * @param      func  The function
 * @param      arg   The argument of the function
 *
 * @return     Returns the initialized task
 */
task_t *init_task(call func, void *arg);

/**
 * @brief      Frees the given task memory
 *
 * @param      task  The task
 *
 * @return     Returns nothing
 */
void free_task(task_t *task);

#endif /*TASK_H_*/