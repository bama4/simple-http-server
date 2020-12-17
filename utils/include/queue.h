#ifndef QUEUE_H
#define QUEUE_H
#include "linked_list.h"

typedef struct queue {
    linked_list_t *_list;
    unsigned int size;
} queue_t;

/**
 * @brief      Initializes the queue.
 *
 * @return     Returns memory allocated for the queue
 */
queue_t *init_queue();

/**
 * @brief      Insert the given data in the queue
 *
 * @param[in]      queue  The queue
 * @param[in]      data   The data to insert
 */
void enqueue(queue_t **queue, void *data);

/**
 * @brief      Remove the next item in the queue
 *
 * @param[in]      queue  The queue
 *
 * @return     Returns the item removed from the queue
 */
void *dequeue(queue_t *queue);

/**
 * @brief      Returns the data at the front of the queue
 *
 * @param[in]      queue  The queue
 *
 * @return     Returns the data at the front of the queue
 */
void *front(queue_t *queue);

/**
 * @brief      Frees the given queue
 *
 * @param[in]      queue  The queue
 */
void free_queue(queue_t *queue);

#endif /*QUEUE_H*/