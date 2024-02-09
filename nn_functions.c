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

void nn_print(nn_t nn, const char *name)
{
    if (nn.bias == NULL) {
        printf("nn_print error : invalid nn\n");
        return;
    }
    printf("\n%s = \n[\n", name);
    mat_print(nn.nodes[0], "\tinput");
    for (int i = 1; i < nn.arch_size; i++) {
        printf("layer [%d]\n", i);
        mat_print(nn.weights[i - 1], "\tweight");
        mat_print(nn.bias[i - 1], "\tbias");
        mat_print(nn.nodes[i], "\toutput");
    }
    printf("]\n");
}

nn_t nn_copy_arch(nn_t *nn)
{
    nn_t cp;

    if (nn->arch_size < 2) {
        printf("nn_copy_arch error : arch size can't be less than 2 layers long\n");
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
    if (td->intput.cols != nn->nodes[0].cols) {
        printf("nn_forward error : inputs aren't well sized\n");
        return;
    }
    mat_copy(&nn->nodes[0], &td->intput);
    mat_act(&nn->nodes[0], ACTIVATION);
    for (int i = 1; i < nn->arch_size; i++) {
        mat_dot(&nn->nodes[i], &nn->nodes[i - 1], &nn->weights[i - 1]);
        mat_sum(&nn->nodes[i], &nn->bias[i - 1]);
        mat_act(&nn->nodes[i], ACTIVATION);
    }
}

void nn_backprop(nn_t *nn, nn_t *g, dat_t **dataset)
{
    float n;
    float dn;
    float pn;
    float w;
    int td_count = 0;
    dat_t *td = *dataset;

    nn_set(g, 0.0);
    if (nn->nodes[0].cols != td->intput.cols) {
        printf("nn_backprop error : inputs are not the same sizes\n");
        return;
    }
    if (nn->nodes[nn->arch_size - 1].cols != td->output.cols) {
        printf("nn_backprop error : outputs are not the same sizes\n");
        return;
    }
    while (td != NULL) {



        nn_forward(nn, td);


        for (int i = 0; i < nn->arch_size; i++)
            mat_set(&g->nodes[i], 0);

        for (int i = 0; i < td->output.cols; i++)
            g->nodes[g->arch_size - 1].matrix[0][i] = nn->nodes[nn->arch_size - 1].matrix[0][i] - td->output.matrix[0][i];

        for (int i = nn->arch_size - 1; i > 0; i--) {
            for (int j = 0; j < nn->nodes[i].cols; j++) {
                n = nn->nodes[i].matrix[0][j];
                dn = g->nodes[i].matrix[0][j];
                g->bias[i - 1].matrix[0][j] += 2 * dn * n * (1 - n);
                for (int k = 0; k < nn->nodes[i - 1].cols; k++) {
                    pn = nn->nodes[i - 1].matrix[0][k];
                    w = nn->weights[i - 1].matrix[k][j];
                    g->weights[i - 1].matrix[k][j] += 2 * dn * n * (1 - n) * pn;
                    g->nodes[i - 1].matrix[0][k] +=  2 * dn * n * (1 - n) * w;
                }
            }
        }
        td_count++;
        td = td->next;
    }
    for (int i = 0; i < g->arch_size - 1; i++) {
        mat_div(&g->weights[i], td_count);
        mat_div(&g->bias[i], td_count);
    }
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

void nn_learn(nn_t *nn, nn_t *g, float rate)
{
    for (int i = 0; i < nn->arch_size - 1; i++) {
        for (int j = 0; j < nn->weights[i].rows; j++) {
            for (int k = 0; k < nn->weights[i].cols; k++)
                nn->weights[i].matrix[j][k] -= rate * g->weights[i].matrix[j][k];
            for (int k = 0; k < nn->bias[i].cols; k++)
                nn->bias[i].matrix[0][k] -= rate * g->bias[i].matrix[0][k];
        }
    }
}

float nn_cost(nn_t *nn, dat_t **dataset)
{
    dat_t *td = *dataset;
    float cost = 0;
    float diff;

    if (nn->nodes[0].cols != td->intput.cols) {
        printf("nn_cost error : inputs are not the same sizes\n");
        return 0;
    }
    if (nn->nodes[nn->arch_size - 1].cols != td->output.cols) {
        printf("nn_cost error : outputs are not the same sizes\n");
        return 0;
    }
    while (td != NULL) {
        nn_forward(nn, td);
        for (int i = 0; i < nn->nodes[nn->arch_size - 1].cols; i++) {
            diff = nn->nodes[nn->arch_size - 1].matrix[0][i] - td->output.matrix[0][i];
            cost += diff*diff;
        }
        td = td->next;
    }
    return cost;
}

void nn_print_results(nn_t *nn, dat_t *td)
{
    nn_forward(nn, td);
    printf("\n");
    for (int i = 0; i < td->intput.cols; i++)
        printf(" %f", td->intput.matrix[0][i]);
    printf("\t=");
    for (int i = 0; i < nn->nodes[nn->arch_size - 1].cols; i++)
        printf(" %f", nn->nodes[nn->arch_size - 1].matrix[0][i]);
    td = td->next;
    printf("\n");
}