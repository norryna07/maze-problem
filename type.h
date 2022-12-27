#ifndef __TYPE_H
#define __TYPE_H

#include <stdio.h>

#define n_max 1005
#define wall -1
#define floor 0
#define initial 1
#define way 2
#define process 3
int dl[]={0, 0, -1, 1};
int dc[]={-1, 1, 0, 0};

typedef struct {int l, c;} position;

/**
 * @brief the element of a singly linked list of position
*/
typedef struct point 
{
    position val;
    struct point *urm;
} point; 

/**
 * @brief the element of a doubly linked list of position
*/
typedef struct point2
{
    position val;
    struct point2 *urm, *ant;
} point2;

/**
 * @brief a doubly linked list of position
 *        ALWAYS set at declaration value to default_list2
*/
typedef struct {point2 *first, *last;} list2;
list2 default_list2 = {0, 0};

/** @brief A queue variable will memorate the adress of
 *          the first and the last element from that queue.
 *          Every element of a queue will stock 2 values:
 *              a line index
 *              a column index
 *        ALWAYS set at declaration value to default_queue
*/
typedef struct {point *first, *last;} queue;
queue default_queue={0, 0};

#endif