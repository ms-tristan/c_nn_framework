/*
** EPITECH PROJECT, 2024
** nn_framework.c
** File description:
** This is th header file of the neural network framework.
*/

#include "nn_framework.h"

void nn_rand(nn_t *nn)
{
    if (nn == NULL || nn->bias == NULL) {
        printf("nn_rand error : invalid nn\n");
        return;
    }
    mat_set(&nn->nodes[0], 0);
    for (int i = 1; i < nn->arch_size; i++) {
        mat_rand(&nn->weights[i - 1]);
        mat_rand(&nn->bias[i - 1]);
        mat_set(&nn->nodes[i], 0);
    }
}

void nn_set(nn_t *nn, float nb)
{
    mat_set(&nn->nodes[0], nb);
    for (int i = 1; i < nn->arch_size; i++) {
        mat_set(&nn->weights[i - 1], nb);
        mat_set(&nn->bias[i - 1], nb);
        mat_set(&nn->nodes[i], nb);
    }
}

void nn_copy(nn_t *dest, nn_t *src)
{
    if (dest->arch_size != src->arch_size) {
        printf("nn_copy error : arch sizes don't fit\n");
        return;
    }
    mat_copy(&dest->nodes[0], &src->nodes[0]);
    for (int i = 1; i < dest->arch_size; i++) {
        mat_copy(&dest->bias[i - 1], &src->bias[i - 1]);
        mat_copy(&dest->weights[i - 1], &src->weights[i - 1]);
        mat_copy(&dest->nodes[i], &src->nodes[i]);
    }
}
