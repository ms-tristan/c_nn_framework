/*
** EPITECH PROJECT, 2024
** matrix_functions.c
** File description:
** Theses functions manage the matrix computing of the nn framework.
*/

#include "nn_framework.h"

void mat_act(mat_t *m, activ_e act)
{
    for (int y = 0; y < m->rows; y++) {
        for (int x = 0; x < m->cols; x++)
            m->matrix[y][x] = activation(m->matrix[y][x], act);
    }
}

static void apply_mutation(mat_t *mat, float mutation_rate, int j, int k)
{
    if (rand() < mutation_rate * RAND_MAX) {
        mat->matrix[j][k] += ((float)rand() / RAND_MAX) - 0.5f;
    }
}

void mat_mutate(mat_t *mat, float mutation_rate)
{
    for (int j = 0; j < mat->rows; j++) {
        for (int k = 0; k < mat->cols; k++) {
            apply_mutation(mat, mutation_rate, j, k);
        }
    }
}
