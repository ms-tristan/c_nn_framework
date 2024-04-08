/*
** EPITECH PROJECT, 2024
** C_NN_FRAMEWORK
** File description:
** nn_interactions_functions
*/

#include "nn_framework.h"

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
