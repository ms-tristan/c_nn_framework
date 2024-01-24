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

    if (arch_size < 3)
        return (nn_t){0, NULL, NULL, NULL};
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

void nn_print(nn_t nn, const char *name)
{
    if (nn.bias == NULL) {
        printf("nn_print error : invalid nn\n");
        return;
    }
    printf("%s = \n[\n", name);
    mat_print(nn.nodes[0], "\tinput");
    for (int i = 1; i < nn.arch_size; i++) {
        printf("layer [%d]\n", i);
        mat_print(nn.weights[i - 1], "\tweight");
        mat_print(nn.bias[i - 1], "\tbias");
        mat_print(nn.nodes[i], "\toutput");
    }
    printf("]\n");
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

void nn_forward(nn_t *nn, dat_t *td)
{
    if (td->inputs_len != nn->nodes[0].cols ||
    td->outputs_len != nn->nodes[nn->arch_size - 1].cols) {
        printf("nn_forward error : inputs aren't well sized\n");
        return;
    }
    for (int i = 0; i < td->inputs_len; i++)
        nn->nodes[0].matrix[0][i] = td->inputs[i];
    for (int i = 1; i < nn->arch_size; i++) {
        mat_dot(&nn->nodes[i], &nn->nodes[i - 1], &nn->weights[i - 1]);
        mat_sum(&nn->nodes[i], &nn->bias[i - 1]);
        mat_sig(&nn->nodes[i]);
    }
}

void nn_free(nn_t *nn)
{
    if (nn == NULL || nn->bias == NULL) {
        printf("nn_free error : neural network doesn't exist\n");
        return;
    }
    free(&nn->nodes[0]);
    for (int i = 1; i < nn->arch_size; i++) {
        free(&nn->bias[i - 1]);
        free(&nn->weights[i - 1]);
        free(&nn->nodes[i]);
    }
}