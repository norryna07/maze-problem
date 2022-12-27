#ifndef __MATRICES_H
#define __MATRICES_H

#include <stdio.h>
#include <assert.h>
#include "type.h"


void getMatrix(char*, int[][n_max], int*, int*, position*, position*);
void initMatrix(int [][n_max], int, int);


/**
 * @brief Create the maze matrix.
 * @param file_name  a string that repesent the file name
 * The file format will be like this:
 *     number_line number_column
 *     number_of_blocked_cell
 *     list of cell with format: (x y)
 *     the start point (x y)
 *     the end point (x y)
 * @param matrix  the matrix 
 * @param nc number of columns
 * @param nl number of lines
 * @param st the start position
 * @param ed the end position
*/
void getMatrix(char *file_name, int matrix[][n_max], int *nl, int *nc, position *st, position *ed)
{
    int err;

    FILE *fr = fopen (file_name, "r"); assert(fr != NULL);
    err = fscanf(fr, "%d %d", nl, nc); assert(err == 2);

    initMatrix(matrix, *nl, *nc);

    int n_cell; 
    err = fscanf(fr, "%d", &n_cell); assert(err == 1);

    int x, y, i;
    for (i = 0; i < n_cell; i++)
    {
        err = fscanf(fr, "%d %d", &x, &y); assert(err == 2);
        assert(!(x < 1 || x > *nl || y < 1 || y > *nc));
        matrix[x][y] = wall;  
    }
    err = fscanf(fr, "%d %d", &st->l, &st->c); assert(err == 2);
    err = fscanf(fr, "%d %d", &ed->l, &ed->c); assert(err == 2); 

    err = fclose(fr); assert(err == 0);
}

/**
 * @brief Initialization of the maze matrix.
 * @param matrix - the matrix
 * @param nl - number of lines
 * @param nc - number of columns
*/
void initMatrix(int matrix[][n_max], int nl, int nc)
{
    int i, j;
    for (i = 0; i <= nl+1; ++i) matrix[i][0] = matrix[i][nc+1] = wall;
    for (j = 0; j <=nc+1; ++j) matrix[0][j] = matrix[nl+1][j] = wall;

    for (i = 1; i <= nl; ++i)
        for (j = 1; j <= nc; ++j)
            matrix[i][j] = floor;
}

#endif