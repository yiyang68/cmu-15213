/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if(q == NULL) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* Remember to free the queue structue and list elements */
    if(q == NULL) return;
    if(q->head != NULL) {
        list_ele_t *e = q->head;
        list_ele_t *tmp = NULL;
        if(e->next != NULL) {
            tmp = e->next;
        }
        while(e != NULL) {
            free(e);
            e = tmp;
            if(e != NULL) {
                tmp = e->next;
            }
        }
    }
    /* Free queue structure */
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    /* What should you do if the q is NULL? */
    /* What if malloc returned NULL? */
    if(!q) return false;
    list_ele_t* node=malloc(sizeof(list_ele_t));
    if(!node) return false;
    node->value=v;
    node->next=q->head;
    q->head=node;
    if(q->size==0) {
        q->tail=q->head;
    }
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    /* Remember: It should operate in O(1) time */
    if(!q) return false;
    list_ele_t* node=malloc(sizeof(list_ele_t));
    if(!node) return false;
    node->value=v;
    node->next=NULL;
    if(q->size==0) {
        q->tail=node;
        q->head=node;
        q->size++;
        return true;
    }
    q->tail->next=node;
    q->tail=node;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    if(!q||!q->head) return false;
    if(vp != NULL) {
        *vp = q->head->value;
    }
    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    free(tmp);
    if(q->size==1)
        q->tail=NULL;
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Remember: It should operate in O(1) time */
    if(!q) return 0;
    return q->size;

}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    if(!q||q->size<=1) return;
    list_ele_t *nex=NULL;
    list_ele_t *pre=NULL;
    list_ele_t *tmp=q->head;
    q->tail=q->head;
    while(tmp) {
        nex=tmp->next;
        tmp->next=pre;
        pre=tmp;
        tmp=nex;
    }
    q->head=pre;
}

