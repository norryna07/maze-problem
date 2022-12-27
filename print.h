#ifndef __PRINT_H
#define __PRINT_H

#include <stdio.h>
#include <assert.h>
#include "type.h"

void printMatrix(char*, int[][n_max], int, int, position, position);
void printPath(char*, position*, int);

/**
 * @brief Write in file the matrix of labirinth
 * @param filename the name of file where the matrix will be write
 * @param matrix the matrix of labirinth
 * @param n number of lines
 * @param m number of columns
*/
void printMatrix(char* filename, int matrix[][n_max], int n, int m, position st, position ed)
{
    int err;
    FILE *fw = fopen(filename, "w"); assert(fw != NULL);
    
    int i, j;
    for (i = 1; i <= n; ++i)
    {
        for (j = 1; j <= m; ++j)
        {
            if (i == st.l && j == st.c) fprintf(fw, " S ");
            else if (i == ed.l && j == ed.c) fprintf(fw, " E ");
                 else fprintf(fw, "%2i ", matrix[i][j]);
        }
        fprintf(fw, "\n");
    }
    err = fclose(fw); assert(err == 0);
}

void printPath(char *filename, position *path, int lg)
{
    FILE *fw = fopen (filename, "w"); assert(fw != NULL);

    int i;
    for (i = 0; i < lg; ++i)
        fprintf(fw, "(%i %i)\n", path[i].l, path[i].c);
    int err = fclose(fw); assert(err == 0);
}

#endif