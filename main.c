#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "queue.h"
#include "type.h"
#include "matrices.h"
#include "way.h"
#include "print.h"
#include "show.h"

int matrix[n_max][n_max]; 
void Task1(char*, int[][n_max]);
void Task2(char*, int[][n_max]);
void Task3(char*, int[][n_max]);
void Task4(char*, int[][n_max]);
void Task5(char*, int[][n_max]);
void Task6(char*, int[][n_max]);

int main()
{
    int err;
    printf("Pentru a incepe introduceti numele fisierului in care se afla labirintul:\n");
    char *filename = (char*)malloc(n_max*sizeof(char));
    err = scanf("%s", filename); assert(err == 1);
    int lg_file = strlen(filename);
    filename = (char*)realloc(filename, (lg_file+1)*sizeof(char));

    printf("\nAlegeti una dintre urmatoarele operatii:\n");
    printf("1. Afisati matricea initiala intr-un fisier.\n");
    printf("2. Afisati matricea dupa prelucrarea intr-un fisier.\n");
    printf("3. Afisati drumul intr-un fisier.\n");
    printf("4. Afisati labirintul initial.\n");
    printf("5. Afisati drumul prin labirint.\n");
    printf("6. Afisati procesul de creeare al drumului.\n");
    printf("Sau E pentru a inchide....\n");

    while (true)
    {   
        char task;
        scanf("%c", &task);
        switch(task)
        {
            case '1': Task1(filename, matrix); break;
            case '2': Task2(filename, matrix); break;
            case '3': Task3(filename, matrix); break;
            case '4': Task4(filename, matrix); break;
            case '5': Task5(filename, matrix); break;
            case '6': Task6(filename, matrix); break;
            case 'E': return 0;
            default: break;
        }
    }
    return 0;
}

/**
 * @brief Afiseaza matricea initiala in fisier
*/
void Task1(char *filename, int matrix[][n_max])
{
    int nl, nc;
    position st, ed;
    getMatrix(filename, matrix, &nl, &nc, &st, &ed);
    printf("Introduceti fisierul in care doriti sa fie afisata matricea:\n");

    char *fout = (char*)malloc(n_max*sizeof(char));
    scanf("%s", fout);
    int lg_fout = strlen(fout);
    fout = (char*)realloc(fout, (lg_fout+1)*sizeof(char));

    printMatrix(fout, matrix, nl, nc, st, ed);
}

/**
 * @brief Afiseaza matricea dupa prelucrare in fisier
*/
void Task2(char *filename, int matrix[][n_max])
{
    int nl, nc;
    position st, ed;
    getMatrix(filename, matrix, &nl, &nc, &st, &ed);
    printf("Introduceti fisierul in care doriti sa fie afisata matricea:\n");

    char *fout = (char*)malloc(n_max*sizeof(char));
    scanf("%s", fout);
    int lg_fout = strlen(fout);
    fout = (char*)realloc(fout, (lg_fout+1)*sizeof(char));

    int lg = ShortWay(matrix, st, ed);
    printMatrix(fout, matrix, nl, nc, st, ed);
}

/**
 * @brief Afiseaza drumul in fisier
*/
void Task3(char *filename, int matrix[][n_max])
{
    int nl, nc;
    position st, ed;
    getMatrix(filename, matrix, &nl, &nc, &st, &ed);
    printf("Introduceti fisierul in care doriti sa fie afisata matricea:\n");

    char *fout = (char*)malloc(n_max*sizeof(char));
    scanf("%s", fout);
    int lg_fout = strlen(fout);
    fout = (char*)realloc(fout, (lg_fout+1)*sizeof(char));

    ShortWay(matrix, st, ed);
    int lg; 
    position *path = getPath(matrix, st, ed, &lg);
    printPath(fout, path, lg);
    free(path);
}

/**
 * @brief Afisati labirindul initial
*/
void Task4(char* filename, int matrix[][n_max])
{
    int nl, nc;
    position st, ed;
    getMatrix(filename, matrix, &nl, &nc, &st, &ed);

    int err = run(matrix, nl, nc, st, ed, 500, 500, "Labirint", initial);
    if (err != 0) {fprintf(stderr, "Deschiderea aplicatiei a esuat!"); exit(0);}    
}

void Task5(char* filename, int matrix[][n_max])
{
    int nl, nc;
    position st, ed;
    getMatrix(filename, matrix, &nl, &nc, &st, &ed);

    ShortWay(matrix, st, ed);
    int lg; 
    position *path = getPath(matrix, st, ed, &lg);
    int err = run(matrix, nl, nc, st, ed, 500, 500, "Labirint", way, path, lg);
    if (err != 0) {fprintf(stderr, "Deschiderea aplicatiei a esuat!"); exit(0);}    
}

void Task6(char* filename, int matrix[][n_max])
{
    int nl, nc;
    position st, ed;
    getMatrix(filename, matrix, &nl, &nc, &st, &ed);

    ShortWay(matrix, st, ed);
    
    int err = run(matrix, nl, nc, st, ed, 500, 500, "Labirint", process);
    if (err != 0) {fprintf(stderr, "Deschiderea aplicatiei a esuat!"); exit(0);} 
}