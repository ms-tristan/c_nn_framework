/*
** EPITECH PROJECT, 2024
** matrix_functions.c
** File description:
** Theses functions manage the matrix computing of the nn framework.
*/

#include "nn_framework.h"

static void mat_dot_cpte(vec3i_t *vec, mat_t *dest, mat_t *src1, mat_t *src2)
{
    for (int k = 0; k < src1->cols; k++) {
        dest->matrix[vec->x][vec->y] += src1->matrix[vec->x][k]
        * src2->matrix[k][vec->y];
    }
}

void mat_dot(mat_t *dest, mat_t *src1, mat_t *src2)
{
    vec3i_t vec;

    if (src1->cols != src2->rows) {
        printf("mat_dot error : src matrices aren't well sized\n");
        return;
    }
    if (dest->rows != src1->rows || dest->cols != src2->cols) {
        printf("mat_dot error : destination matrix isn't well sized\n");
        return;
    }
    mat_set(dest, 0);
    for (int i = 0; i < src1->rows; i++) {
        for (int j = 0; j < src2->cols; j++) {
            vec = (vec3i_t){i, j, 0};
            mat_dot_cpte(&vec, dest, src1, src2);
        }
    }
}

void mat_div(mat_t *m, int div)
{
    for (int y = 0; y < m->rows; y++) {
        for (int x = 0; x < m->cols; x++) {
            m->matrix[y][x] /= div;
        }
    }
}

void mat_substract(mat_t *dest, mat_t *src)
{
    if (src->cols != dest->cols || src->rows != dest->rows) {
        printf("mat_sub error : matrices have to be the same size\n");
        return;
    }
    for (int y = 0; y < dest->rows; y++) {
        for (int x = 0; x < dest->cols; x++)
            dest->matrix[y][x] -= src->matrix[y][x];
    }
}

void mat_sum(mat_t *dest, mat_t *src)
{
    if (src->cols != dest->cols || src->rows != dest->rows) {
        printf("mat_sum error : matrices have to be the same size\n");
        return;
    }
    for (int y = 0; y < dest->rows; y++) {
        for (int x = 0; x < dest->cols; x++)
            dest->matrix[y][x] += src->matrix[y][x];
    }
}

void mat_rand(mat_t *m)
{
    if (m->cols < 1 || m->rows < 1) {
        printf("mat_rand error : matrix is not well allocated\n");
        return;
    }
    for (int y = 0; y < m->rows; y++) {
        for (int x = 0; x < m->cols; x++)
            m->matrix[y][x] = (activation(rand_mm(0, 4), ACTIVATION));
    }
}
