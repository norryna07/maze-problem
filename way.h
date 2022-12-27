#ifndef __WAY_H
#define __WAY_H

#include <stdio.h>
#include "type.h"
#include "queue.h"
#include "list2.h"

int ShortWay(int[][n_max], position, position);
position* getPath(int[][n_max], position, position, int*);


/**
 * @brief Create the shortest way from the start point to end point and returns the number of steps
 * @return the number of steps or -1 if the end point can't be reach 
 * @param matrix the maze matrix
 * @param st the start position
 * @param ed the end position
*/
int ShortWay(int matrix[][n_max], position st, position ed)
{
    queue q;
    q = default_queue;
    queue_push(&q, st);
    matrix[st.l][st.c] = 1;
    while (!queue_empty(q))
    {
        position x = queue_front(q); queue_pop(&q);

        int k;
        for (k = 0; k < 4; ++k)
        {
            position next = {x.l+dl[k], x.c+dc[k]};
            if (matrix[next.l][next.c] == floor)
            {
                matrix[next.l][next.c] = matrix[x.l][x.c] + 1;
                if (next.l == ed.l && next.c == ed.c) return matrix[next.l][next.c] - 1;
                queue_push(&q, next);
            }
        }
    }
    return -1;
}

/**
 * @brief Create a list with all steps on the shortest way from start to end
 * @param matrix The matrix generate by function ShortWay
 * @param st the start position
 * @param ed the end position
 * @param lg the number of elements from path
 * @return a position pointer for the path
*/
position* getPath(int matrix[][n_max], position st, position ed, int* lg)
{
    position poz = ed;
    position *path;
    int pas = matrix[ed.l][ed.c];
    *lg = pas;
    if (pas == 0) {path = NULL; return path;}

    path = (position*)malloc(pas*sizeof(position));
    path[pas-1] = poz;
    while (poz.l != st.l || poz.c != st.c)
    {
        int k;
        for (k = 0; k < 4; k++)
        {
            position now = {poz.l+dl[k], poz.c+dc[k]};
            if (matrix[now.l][now.c]==pas-1)
            {
                poz = now;
                pas--;
                path[pas-1] = poz;
                break;
            }
        }
    }
    return path;
}


#endif
