/*
** EPITECH PROJECT, 2024
** C_NN_FRAMEWORK
** File description:
** nn_saving_functions
*/

#include "nn_framework.h"

static void matrix_save(mat_t *mat, FILE *file)
{
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++)
            fprintf(file, "%f ", mat->matrix[i][j]);
        fprintf(file, "\n");
    }
}

void nn_save(nn_t *nn, const char *path)
{
    FILE *file = fopen(path, "w");

    if (file == NULL) {
        printf("nn_save error : invalid file\n");
        return;
    }
    fprintf(file, "%d\n", nn->arch_size);
    for (int i = 0; i < nn->arch_size; i++)
        fprintf(file, "%d ", nn->nodes[i].cols);
    fprintf(file, "\n");
    for (int i = 0; i < nn->arch_size - 1; i++) {
        matrix_save(&nn->weights[i], file);
        matrix_save(&nn->bias[i], file);
    }
}

static void mat_read(mat_t *mat, FILE *file)
{
    for (int i = 0; i < mat->rows; i++)
        for (int j = 0; j < mat->cols; j++)
            fscanf(file, "%f ", &mat->matrix[i][j]);
}

nn_t nn_open(const char *path)
{
    FILE *file = fopen(path, "r");
    nn_t nn;
    int arch_size;
    int *arch;

    if (file == NULL) {
        printf("nn_open error : invalid file\n");
        return (nn_t){0, NULL, NULL, NULL};
    }
    fscanf(file, "%d\n", &arch_size);
    arch = malloc(sizeof(int) * arch_size);
    for (int i = 0; i < arch_size; i++)
        fscanf(file, "%d ", &arch[i]);
    nn = nn_init(arch, arch_size);
    for (int i = 0; i < nn.arch_size - 1; i++) {
        mat_read(&nn.weights[i], file);
        mat_read(&nn.bias[i], file);
    }
    free(arch);
    return nn;
}
