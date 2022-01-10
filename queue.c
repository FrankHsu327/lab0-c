#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (!q)
        return NULL;
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* Return NULL if q is NULL */
    if (!q)
        return;

    /* Free every node and its element */
    while (q->head) {
        list_ele_t *tmp = q->head;
        q->head = tmp->next;
        free(tmp->value);
        free(tmp);
    }

    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    char *new_s;

    /* If q is NULL, return false */
    if (!q)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;

    /* Allocate space for string and copy s to it */
    new_s = malloc((strlen(s) + 1) * sizeof(char));  // +1 is for the terminator
    if (!new_s) {
        free(newh);
        return false;
    }
    strncpy(new_s, s, (strlen(s) + 1));

    /* Assign value */
    newh->value = new_s;
    newh->next = q->head;

    /* Modify the queue*/
    q->head = newh;
    if (!q->tail)
        q->tail = q->head;
    q->size += 1;

    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* Remember: It should operate in O(1) time */
    list_ele_t *newt;
    char *new_s;

    /* If q is NULL, return false */
    if (!q)
        return false;

    newt = malloc(sizeof(list_ele_t));
    if (!newt)
        return false;

    /* Allocate space for string and copy s to it */
    new_s = malloc((strlen(s) + 1) * sizeof(char));  // +1 is for the terminator
    if (!new_s) {
        free(newt);
        return false;
    }
    strncpy(new_s, s, (strlen(s) + 1));

    /* Assign value */
    newt->value = new_s;
    newt->next = NULL;

    /* Modify queue */
    if (!q->tail) {
        q->head = newt;
        q->tail = newt;
    } else {
        q->tail->next = newt;
        q->tail = newt;
    }
    q->size += 1;

    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    list_ele_t *tmp;
    /* Check eligibility of q */
    if (!q || !q->head)
        return false;

    /* copy removed string to sp if sp is not NULL*/
    if (sp) {
        size_t len = strlen(q->head->value) + 1;

        /* Compare bufsize to len */
        len = bufsize < len ? bufsize : len;

        strncpy(sp, q->head->value, len - 1);
        sp[len - 1] = '\0';
    }

    tmp = q->head;
    q->head = q->head->next;
    free(tmp->value);
    free(tmp);
    q->size -= 1;

    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q ? q->size : 0;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    list_ele_t *curr, *next;

    /* Check eligibility of q */
    if (!q || !q->head)
        return;

    q->tail = q->head;
    curr = q->head;
    q->head = NULL;

    while (curr) {
        next = curr->next;
        curr->next = q->head;
        q->head = curr;
        curr = next;
    }
}

// static list_ele_t *q_divide(queue_t *q)
// {
//     return;
// }
/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    if (q)
        return;
}
