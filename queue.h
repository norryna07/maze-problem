#ifndef __QUEUE_H
#define __QUEUE_H

#include <stdbool.h>
#include <stdlib.h>
#include "type.h"

position queue_front(queue);
void queue_pop(queue *);
void queue_push(queue *, position);
bool queue_empty(queue);
void queue_free(queue *);

/** @brief The function return the front element from the queue q.
 *  @param q  a queue where to search the front element
 *  @return a position variable with 2 values: line and column
 *          or (-1, -1) if the q has no element
 */
position queue_front(queue q)
{
    if (q.first == 0)
    {
        position x = {-1, -1};
        return x;
    }
    return q.first->val;
}

/** @brief The function delete the frist/front element form the queue q.
 *  @param q  an adress of a queue from where delete the front element
 */
void queue_pop(queue *q)
{
    if (q->first == 0)
        return;
    point *p = q->first;
    q->first = q->first->urm;
    if (q->first == 0) q->last = 0;
    free(p);
}

/** @brief Put the position x on the end of queue q
 * @param q  an adress of a queue that will be updated
 * @param x  a position that will be add
 */
void queue_push(queue *q, position x)
{
    point *p = (point*)malloc(sizeof(point));
    p->urm = 0;
    p->val = x;
    if (q->last != 0)
        q->last->urm = p;
    else
        q->first = p;
    q->last = p;
}

/** @brief Verify if the queue q is empty
 *  @param q  a queue variable
 *  @return 1 - if q is empty
 *          0 - if q is not empty
 */
bool queue_empty(queue q)
{
    if (q.first == 0)
        return 1;
    return 0;
}

/**
 * @brief Deallocate the memory used for queue
 * @param q The queue that will be dealocated
 */
void queue_free(queue *q)
{
    while (q->first != NULL)
        queue_pop(q);
}

#endif