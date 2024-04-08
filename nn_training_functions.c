/*
** EPITECH PROJECT, 2024
** nn_framework.c
** File description:
** This is th header file of the neural network framework.
*/

#include "nn_framework.h"

void nn_forward(nn_t *nn, dat_t *td)
{
    if (td->intput.cols != nn->nodes[0].cols) {
        printf("nn_forward error : inputs aren't well sized\n");
        return;
    }
    mat_copy(&nn->nodes[0], &td->intput);
    for (int i = 1; i < nn->arch_size; i++) {
        mat_dot(&nn->nodes[i], &nn->nodes[i - 1], &nn->weights[i - 1]);
        mat_sum(&nn->nodes[i], &nn->bias[i - 1]);
        mat_act(&nn->nodes[i], ACTIVATION);
    }
}

static void backprop_to_gradient(nn_t *nn, nn_t *g, int i)
{
    float dn;
    float pn;
    float n;
    float w;

    for (int j = 0; j < nn->nodes[i].cols; j++) {
        n = nn->nodes[i].matrix[0][j];
        dn = g->nodes[i].matrix[0][j];
        g->bias[i - 1].matrix[0][j] += 2 * dn * n * (1 - n);
        for (int k = 0; k < nn->nodes[i - 1].cols; k++) {
            pn = nn->nodes[i - 1].matrix[0][k];
            w = nn->weights[i - 1].matrix[k][j];
            g->weights[i - 1].matrix[k][j] += 2 * dn * n * (1 - n) * pn;
            g->nodes[i - 1].matrix[0][k] += 2 * dn * n * (1 - n) * w;
        }
    }
}

static void nn_backprop(nn_t *nn, nn_t *g, dat_t *data)
{
        for (int i = 0; i < nn->arch_size; i++)
            mat_set(&g->nodes[i], 0);
        for (int i = 0; i < data->output.cols; i++) {
            g->nodes[g->arch_size - 1].matrix[0][i] =
            nn->nodes[nn->arch_size - 1].matrix[0][i] -
            data->output.matrix[0][i];
        }
        for (int i = nn->arch_size - 1; i > 0; i--) {
            backprop_to_gradient(nn, g, i);
        }
}

static int check_for_errors(nn_t *nn, dat_t *td)
{
    if (nn->nodes[0].cols != td->intput.cols) {
        printf("nn_backprop error : inputs are not the same sizes\n");
        return 0;
    } else if (nn->nodes[nn->arch_size - 1].cols != td->output.cols) {
        printf("nn_backprop error : outputs are not the same sizes\n");
        return 0;
    }
    return 1;
}

void nn_train(nn_t *nn, nn_t *g, dat_t **dataset)
{
    int training_count = 0;
    dat_t *td = *dataset;

    nn_set(g, 0.0);
    if (!check_for_errors(nn, td))
        return;
    while (td) {
        nn_forward(nn, td);
        nn_backprop(nn, g, td);
        training_count++;
        td = td->next;
    }
    for (int i = 0; i < g->arch_size - 1; i++) {
        mat_div(&g->weights[i], training_count);
        mat_div(&g->bias[i], training_count);
    }
}

static void apply_to_w_b(nn_t *nn, nn_t *g, float rate, vec3i_t *vec)
{
    for (int k = 0; k < nn->weights[vec->x].cols; k++) {
        nn->weights[vec->x].matrix[vec->y][k] -= rate *
        g->weights[vec->x].matrix[vec->y][k];
    }
    for (int k = 0; k < nn->bias[vec->x].cols; k++) {
        nn->bias[vec->x].matrix[0][k] -= rate *
        g->bias[vec->x].matrix[0][k];
    }
}

void nn_apply_gradient(nn_t *nn, nn_t *g, float rate)
{
    vec3i_t vec;

    for (int i = 0; i < nn->arch_size - 1; i++) {
        for (int j = 0; j < nn->weights[i].rows; j++) {
            vec = (vec3i_t){i, j, 0};
            apply_to_w_b(nn, g, rate, &vec);
        }
    }
}

static int check_for_cost_errors(nn_t *nn, dat_t *td)
{
    if (nn->nodes[0].cols != td->intput.cols) {
        printf("nn_cost error : inputs are not the same sizes\n");
        return 0;
    } else if (nn->nodes[nn->arch_size - 1].cols != td->output.cols) {
        printf("nn_cost error : outputs are not the same sizes\n");
        return 0;
    }
}

float nn_cost(nn_t *nn, dat_t **dataset)
{
    dat_t *td = *dataset;
    float cost = 0;
    float diff;

    if (!check_for_cost_errors(nn, td))
        return 0;
    while (td != NULL) {
        nn_forward(nn, td);
        for (int i = 0; i < nn->nodes[nn->arch_size - 1].cols; i++) {
            diff = nn->nodes[nn->arch_size - 1].matrix[0][i] -
            td->output.matrix[0][i];
            cost += diff * diff;
        }
        td = td->next;
    }
    return cost;
}

void nn_mutate(nn_t *nn, float mutation_rate)
{
    for (int i = 0; i < nn->arch_size - 1; i++) {
        for (int j = 0; j < nn->bias[i].cols; j++) {
            mat_mutate(&nn->bias[i], mutation_rate);
            mat_mutate(&nn->weights[i], mutation_rate);
        }
    }
}