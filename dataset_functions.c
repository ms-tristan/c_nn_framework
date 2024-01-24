/*
** EPITECH PROJECT, 2024
** dataset_functions.c
** File description:
** Theses functions make the dataset managment easier for the neural network.
*/

#include "nn_framework.h"

dat_t datasheet_init(float *inputs, int ip_len, float *outputs, int op_len)
{
    dat_t datasheet;

    datasheet.inputs = inputs;
    datasheet.expected_outputs = outputs;
    datasheet.inputs_len = ip_len;
    datasheet.outputs_len = op_len;
    return datasheet;
}

void dataset_append(dat_t **dataset, dat_t *datasheet)
{
    datasheet->next = *dataset;
    *dataset = datasheet;
}

static void print_float_array(float *array, int len)
{
    for (int i = 0; i < len; i++)
        printf("%.2f  ", array[i]);
    printf("\n");
}

void dataset_print(dat_t *dataset)
{
    while (dataset != NULL) {
        printf("inputs :\n\t");
        print_float_array(dataset->inputs, dataset->inputs_len);
        printf("\noutputs\n\t");
        print_float_array(dataset->expected_outputs, dataset->outputs_len);
        printf("\n");
        dataset = dataset->next;
    }
}
