/*
** EPITECH PROJECT, 2024
** matrix_functions.c
** File description:
** Theses functions manage the matrix computing of the nn framework.
*/

#include "nn_framework.h"

mat_t mat_init(int rows, int cols)
{
    mat_t m;

    if (rows < 1 || cols < 1) {
        printf("mat_init error : matrix size doesn't fit\n");
        return (mat_t){0, 0, NULL};
    }
    m.rows = rows;
    m.cols = cols;
    m.matrix = malloc(sizeof(float *) * rows);
    for (int y = 0; y < rows; y++)
        m.matrix[y] = malloc(sizeof(float) * cols);
    mat_rand(&m);
    return m;
}

void mat_print(mat_t m, const char *name)
{
    if (m.matrix == NULL) {
        printf("mat_print error : matrix doesn't exist\n");
        return;
    }
    printf("%s =\n\t[\n\t", name);
    for (int y = 0; y < m.rows; y++) {
        for (int x = 0; x < m.cols; x++) {
            printf("\t%f", m.matrix[y][x]);
        }
        printf("\n\t");
    }
    printf("]\n\n");
}

void mat_set(mat_t *m, int nb)
{
    for (int y = 0; y < m->rows; y++) {
        for (int x = 0; x < m->cols; x++) {
            m->matrix[y][x] = nb;
        }
    }
}

void mat_copy(mat_t *dest, mat_t *src)
{
    if (dest->cols != src->cols || dest->rows != src->rows) {
        printf("mat_copy error : matrices aren't the same size\n");
        return;
    }
    if (dest->matrix == NULL || src->matrix == NULL) {
        printf("mat_copy error : matrices aren't well allocated\n");
        return;
    }
    for (int y = 0; y < dest->rows; y++) {
        for (int x = 0; x < dest->cols; x++)
            dest->matrix[y][x] = src->matrix[y][x];
    }
}

void mat_free(mat_t *m)
{
    if (m->matrix == NULL) {
        printf("mat_free error : matrix doesn't exist\n");
        return;
    }
    for (int i = 0; i < m->rows; i++)
        free(m->matrix[i]);
}
