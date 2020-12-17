#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief      Prints data of a linked list.
 *
 * @param[in]      list  The list to print
 */
void print_linked_list(linked_list_t *list) {
    // Check for NULL
    if (list == NULL) {
        return;
    }
    node_t *curr_node = NULL;
    for (curr_node = list->head; curr_node != NULL;
         curr_node = curr_node->next) {
        printf("%s\n", (char *)curr_node->data);
    }
}

/**
 * @brief      Initializes the linked list
 *
 * @return     Returns an empty linked list
 */
linked_list_t *init_list() {
    linked_list_t *list = (linked_list_t *)calloc(1, sizeof(linked_list_t));

    // Check NULL
    if (list == NULL) {
        return NULL;
    }
    return list;
}

/**
 * @brief      Returns the data from the tail of the list
 *
 * @param[in]      list  The list
 *
 * @return     Returns the last item in the list
 */
void *get_tail(linked_list_t *list) {
    // Check for NULL
    if (list == NULL) {
        return NULL;
    }

    // Return tail data if not NULL
    if (list->tail != NULL) {
        return list->tail->data;
    }

    return NULL;
}

/**
 * @brief      Insert data into the given linked list
 *
 * @param[in]  list  The list for insertion
 * @param[in]  data  The data to insert
 *
 * @return     Returns the node that the data was inserted into else NULL if not
 * found
 */
node_t *insert_data(linked_list_t *list, void *data) {
    // Check for NULL
    if (list == NULL) {
        return NULL;
    }

    node_t *new_node = (node_t *)calloc(1, sizeof(node_t));

    // Check for NULL
    if (new_node == NULL) {
        return NULL;
    }

    if (list->head == NULL) {
        // Make this entry the head
        list->head = new_node;
        list->head->next = NULL;
        list->head->data = data;
        list->tail = list->head;
    } else {
        // Insert as new head
        node_t *temp = list->head;
        new_node->data = data;
        new_node->next = temp;
        list->head = new_node;
    }

    return new_node;
}

/**
 * @brief      Removes the given data from the list; does not free the data
 *
 * @param[in]  list  The list for removal
 * @param[in]  data  The data to remove
 *
 * @return     Returns a pointer to the data that was removed, else NULL if not
 * found
 */
void *remove_data(linked_list_t *list, void *data) {
    // Check for NULL
    if (list == NULL) {
        return NULL;
    }

    // Check for empty list
    if (list->head == NULL) {
        return NULL;
    }

    node_t *prev_node = list->head;

    // Search for data
    node_t *curr_node = list->head;
    while (curr_node != NULL) {

        // If data found
        if (curr_node->data == data) {
            node_t *new_next = curr_node->next;

            // Update tail if necessary
            if (curr_node == list->tail) {
                list->tail = (new_next != NULL) ? new_next : prev_node;
            }

            // If data is at head
            if (curr_node == list->head) {
                list->head = new_next;

                free(curr_node);
                curr_node = NULL;
                return data;
            }

            // If data is not at head
            prev_node->next = new_next;

            free(curr_node);
            curr_node = NULL;
            return data;
        }
        prev_node = curr_node;
        curr_node = curr_node->next;
    }

    // Not found
    return NULL;
}

/**
 * @brief      Removes a tail.
 *
 * @param[in]      list  The list
 *
 * @return     Returns the data contained in the tail
 */
void *remove_tail(linked_list_t *list) {
    void *data = NULL;
    // Check for NULL
    if (list == NULL) {
        return NULL;
    }

    node_t *prev_node = list->head;
    node_t *curr_node = list->head;

    // Check if only one head node in list
    if (list->head == list->tail) {
        data = list->head->data;
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
        return data;
    }

    // If there is more than one node in list
    while (curr_node != NULL) {
        if (curr_node == list->tail) {
            list->tail = prev_node;
            data = curr_node->data;
            free(curr_node);
            curr_node = NULL;
            list->tail->next = NULL;
            break;
        }
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
    return data;
}

/**
 * @brief      Free the given linked list (excluding the data)
 *
 * @param[in]  list  The list to free
 */
void free_list(linked_list_t *list) {
    // Do not free a NULL ptr
    if (list == NULL) {
        return;
    }

    // If empty list, just free list
    if (list->head == NULL) {
        free(list);
        return;
    }

    // Search for data
    node_t *curr_node = list->head;
    node_t *next = NULL;
    while (curr_node != NULL) {

        // Free node
        next = curr_node->next;
        free(curr_node);
        curr_node = NULL;
        curr_node = next;
    }

    list->head = NULL;
    list->tail = NULL;
    free(list);
}