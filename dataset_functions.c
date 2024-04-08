/*
** EPITECH PROJECT, 2024
** dataset_functions.c
** File description:
** Theses functions make the dataset managment easier for the neural network.
*/

#include "nn_framework.h"

dat_t *datasheet_init(float *inputs, int ip_len, float *outputs, int op_len)
{
    dat_t *datasheet = malloc(sizeof(dat_t));

    datasheet->intput = mat_init(1, ip_len);
    datasheet->output = mat_init(1, op_len);
    for (int i = 0; i < ip_len; i++)
        datasheet->intput.matrix[0][i] = inputs[i];
    for (int i = 0; i < op_len; i++)
        datasheet->output.matrix[0][i] = outputs[i];
    return datasheet;
}

void dataset_append(dat_t **dataset, dat_t *datasheet)
{
    if (*dataset != NULL) {
        if (dataset[0]->intput.cols != datasheet->intput.cols ||
        dataset[0]->output.cols != datasheet->output.cols) {
            printf("dataset_append error : datasheet are not well sized\n");
            return;
        }
    }
    datasheet->next = *dataset;
    *dataset = datasheet;
}

void dataset_print(dat_t **dt)
{
    dat_t *dataset = *dt;

    while (dataset != NULL) {
        printf("Datasheet :\n\t");
        mat_print(dataset->intput, "input");
        printf("\t");
        mat_print(dataset->output, "expected output");
        printf("\n");
        dataset = dataset->next;
    }
}

void dataset_free(dat_t **dataset)
{
    dat_t *td = *dataset;
    dat_t *temp;

    while (td != NULL) {
        temp = td;
        mat_free(&td->intput);
        mat_free(&td->output);
        td = td->next;
        free(temp);
    }
}
