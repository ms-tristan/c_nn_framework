/*
** EPITECH PROJECT, 2024
** nn_framework.c
** File description:
** This is th header file of the neural network framework.
*/

#include "nn_framework.h"

nn_t nn_init(int *arch, int arch_size)
{
    nn_t nn;

    if (arch_size < 2) {
        printf("nn_init error : arch size can't be less than 2 layers long\n");
        return (nn_t){0, NULL, NULL, NULL};
    }
    nn.arch_size = arch_size;
    nn.weights = malloc(sizeof(mat_t) * (nn.arch_size - 1));
    nn.bias = malloc(sizeof(mat_t) * (nn.arch_size - 1));
    nn.nodes = malloc(sizeof(mat_t) * (nn.arch_size));
    nn.nodes[0] = mat_init(1, arch[0]);
    for (int i = 1; i < nn.arch_size; i++) {
        nn.weights[i - 1] = mat_init(arch[i - 1], arch[i]);
        nn.bias[i - 1] = mat_init(1, arch[i]);
        nn.nodes[i] = mat_init(1, arch[i]);
    }
    return nn;
}

nn_t nn_copy_arch(nn_t *nn)
{
    nn_t cp;

    if (nn->arch_size < 2) {
        printf("nn_copy_arch error : arch size can't be less than 2\n");
        return (nn_t){0, NULL, NULL, NULL};
    }
    cp.arch_size = nn->arch_size;
    cp.weights = malloc(sizeof(mat_t) * (cp.arch_size - 1));
    cp.bias = malloc(sizeof(mat_t) * (cp.arch_size - 1));
    cp.nodes = malloc(sizeof(mat_t) * (cp.arch_size));
    cp.nodes[0] = mat_init(nn->nodes[0].rows, nn->nodes[0].cols);
    for (int i = 1; i < cp.arch_size; i++) {
        cp.weights[i - 1] = mat_init(nn->nodes[i - 1].cols, nn->nodes[i].cols);
        cp.bias[i - 1] = mat_init(1, nn->nodes[i].cols);
        cp.nodes[i] = mat_init(nn->nodes[i].rows, nn->nodes[i].cols);
    }
    return cp;
}

void nn_free(nn_t *nn)
{
    if (nn == NULL || nn->bias == NULL) {
        printf("nn_free error : neural network doesn't exist\n");
        return;
    }
    mat_free(&nn->nodes[0]);
    for (int i = 1; i < nn->arch_size; i++) {
        mat_free(&nn->bias[i - 1]);
        mat_free(&nn->weights[i - 1]);
        mat_free(&nn->nodes[i]);
    }
}
