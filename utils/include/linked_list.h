#ifndef LINKED_LIST_H
#define LINKED_LIST_H

/**
 * Defines a node of a linked list
 */
typedef struct node {
    void *data;
    struct node *next;
} node_t;

/**
 * Defines a linked list
 */
typedef struct linked_list {
    node_t *head;
    node_t *tail;
} linked_list_t;

/**
 * @brief      Prints a linked list
 *
 * @param[in]      list  The list to print
 */
void print_linked_list(linked_list_t *list);

/**
 * @brief      Initializes the linked list
 *
 * @return     Returns an empty linked list
 */
linked_list_t *init_list();

/**
 * @brief      Returns the data from the tail of the list
 *
 * @param[in]      list  The list
 *
 * @return     Returns the last item in the list
 */
void *get_tail(linked_list_t *list);

/**
 * @brief      Insert data at the head into the given linked list
 *
 * @param[in]  list  The list for insertion
 * @param[in]  data  The data to insert
 *
 * @return     Returns the node that the data was inserted into else NULL if not
 * found
 */
node_t *insert_data(linked_list_t *list, void *data);

/**
 * @brief      Removes the given data from the list; does not free the data
 *
 * @param[in]  list  The list for removal
 * @param[in]  data  The data to remove
 *
 * @return     Returns a pointer to the data that was removed, else NULL if not
 * found
 */
void *remove_data(linked_list_t *list, void *data);

/**
 * @brief      Removes a tail.
 *
 * @param[in]      list  The list
 *
 * @return     Returns the data contained in the tail
 */
void *remove_tail(linked_list_t *list);

/**
 * @brief      Free the given linked list (excluding the data)
 *
 * @param[in]  list  The list to free
 */
void free_list(linked_list_t *list);

#endif /*LINKED_LIST_H*/