#ifndef __LIST2_H
#define __LIST2_H

#include "type.h"
#include <stdlib.h>

void list2_add_front(list2*, position);
void list2_add_back(list2*, position);
void list2_delete_front(list2*);
void list2_delete_back(list2*);
void list2_free(list2*);


/**
 * @brief Add x as first element in the list l
 * @param l a pointer for a list2
 * @param x the number to add
*/
void list2_add_front(list2* l, position x)
{
    point2 *nou = (point2*)malloc(sizeof(point2));
    nou->ant = NULL;
    nou->urm = l->first;
    nou->val = x;
    l->first = nou;
    if (l->last == NULL) l->last = nou;
}

/**
 * @brief Add x as last element in the list l
 * @param l a pointer for a list2
 * @param x the number to add
*/
void list2_add_back(list2* l, position x)
{
    point2 *nou = (point2*)malloc(sizeof(point2));
    nou->urm = NULL;
    nou->ant = l->last;
    nou->val = x;
    l->last = nou;
    if (l->first == NULL) l->first = nou;
}

/**
 * @brief Delete the first element of the list l
 * @param l pointer for a list2
*/
void list2_delete_front(list2* l)
{
    if (l->first == NULL) return;
    point2 *p = l->first;
    l->first = l->first->urm;
    if (l->first == NULL) l->last = NULL;
    free(p);
}

/**
 * @brief Delete the last element of the list l
 * @param l pointer for a list2
*/
void list2_delete_back(list2* l)
{
    if (l->last == NULL) return;
    point2 *p = l->last;
    l->last = l->last->ant;
    if (l->last == NULL) l->first = NULL;
    free(p);
}

/**
 * @brief Dealocate the space used for list l
 * @param l a pointer for the list to dealocate
*/
void list2_free(list2* l)
{
    while (l->first != NULL)
        list2_delete_front(l);
}

#endif