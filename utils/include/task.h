#ifndef TASK_H_
#define TASK_H_

typedef void (*auto_callback)(void);

/*
 Structure for defining task args for a thread
 */
typedef struct task_arg {
    auto_callback pre_task_callback;
    auto_callback post_task_callback;
    void *arg;
} task_arg_t;

typedef void *(*call)(void *task_arg);

/*
  Defines a task object
 */
typedef struct {

    call func;      /*function to be called*/
    task_arg_t arg; /*function arguments*/
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
 * @brief      Initializes the task values.
 *
 * @param      task  The task to set the values for
 * @param      func  The function
 * @param      arg   The argument of the function
 *
 * @return     Returns the initialized task
 */
void init_task_values(task_t *task, call func, void *arg);

/**
 * @brief    Called before each tasks callback when spun off as a thread
 */
void pre_task_callback();

/**
 * @brief    Called after each tasks callback when spun off as a thread
 */
void post_task_callback();

/**
 * @brief      Frees the given task memory
 *
 * @param      task  The task
 *
 * @return     Returns nothing
 */
void free_task(task_t *task);

#endif /*TASK_H_*/