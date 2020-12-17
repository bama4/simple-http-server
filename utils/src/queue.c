#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief      Initializes the queue.
 *
 * @return     Returns memory allocated for the queue
 */
queue_t *init_queue() {
    queue_t *new_queue = (queue_t *)calloc(1, sizeof(queue_t));

    // Check for NULL
    if (new_queue == NULL) {
        return NULL;
    }
    new_queue->_list = init_list();

    // Check for NULL
    if (new_queue->_list == NULL) {
        return NULL;
    }

    new_queue->size = 0;
    return new_queue;
}

/**
 * @brief      Insert the given data in the queue
 *
 * @param[in]      queue  The queue
 * @param[in]      data   The data to insert
 */
void enqueue(queue_t **queue, void *data) {

    // Check for NULL
    if (queue == NULL) {
        return;
    }

    if (*queue == NULL) {
        return;
    }

    // Add data to queue list
    insert_data((*queue)->_list, data);

    // Increment size
    (*queue)->size++;
}

/**
 * @brief      Remove the next item in the queue
 *
 * @param[in]      queue  The queue
 *
 * @return     Returns the item removed from the queue
 */
void *dequeue(queue_t *queue) {

    // Check for NULL
    if (queue == NULL) {
        return NULL;
    }

    // Check for empty queue
    if (queue->size == 0) {
        return NULL;
    }

    // Decrement size
    queue->size--;
    return remove_tail(queue->_list);
}

/**
 * @brief      Returns the data at the front of the queue
 *
 * @param[in]      queue  The queue
 *
 * @return     Returns the data at the front of the queue
 */
void *front(queue_t *queue) {

    // Check for NULL
    if (queue == NULL) {
        return NULL;
    }

    return get_tail(queue->_list);
}

/**
 * @brief      Frees the given queue
 *
 * @param[in]      queue  The queue
 */
void free_queue(queue_t *queue) {
    // Do not free a NULL ptr
    if (queue == NULL) {
        return;
    }
    free_list(queue->_list);
    queue->_list = NULL;
    free(queue);
}