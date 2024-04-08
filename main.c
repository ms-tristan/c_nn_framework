/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** This is the main file of the neural network framework.
*/

#include "nn_framework.h"

static dat_t *array_to_datasheet(char **array, int ipl, int opl)
{
    dat_t *datasheet = malloc(sizeof(dat_t));
    mat_t input = mat_init(1, ipl);
    mat_t output = mat_init(1, opl);

    for (int i = 0; i < ipl + opl; i++) {
        if (array[i] == NULL) {
            printf("array_to_datasheet error : line to short\n");
            return NULL;
        }
        if (i < ipl) {
            input.matrix[0][i] = (float)atoi(array[i]);
            continue;
        }
        output.matrix[0][i - ipl] = (float)atoi(array[i]);
    }
    datasheet->intput = input;
    datasheet->output = output;
    for (int i = 0; array[i] != NULL; i++)
        free(array[i]);
    free(array);
    return datasheet;
}

static dat_t **file_to_dataset(int argc, char **argv)
{
    dat_t **head = malloc(sizeof(dat_t *));
    dat_t *dataset = NULL;
    FILE *file = fopen(argv[1], "r");
    int input_size = atoi(argv[2]);
    int output_size = atoi(argv[argc - 1]);
    char *line = NULL;
    size_t len = 0;

    if (file == NULL) {
        printf("file_to_dataset error : file couldn't open\n");
        return NULL;
    }
    *head = dataset;
    while (getline(&line, &len, file) > 0) {
        dataset_append(head, array_to_datasheet(my_str_to_word_array(line), input_size, output_size));
    }
    free(line);
    return head;
}

int main(int argc, char **argv)
{

    nn_t nn = nn_open("nn_save.txt");
    dat_t **dataset = file_to_dataset(argc, argv);

    // srand(time(NULL));
    // int arch[] = {2, 2, 1};
    // nn_t nn = NN_INIT(arch);
    // nn_print(nn, "nn");>

    nn_t g = nn_copy_arch(&nn);

    for (int i = 0; i < 100; i++) {
        nn_train(&nn, &g, dataset);
        nn_apply_gradient(&nn, &g, 0.01);
        printf("%f\n", nn_cost(&nn, dataset));

    }
    // nn_print(nn, "nn");
    nn_print_results(&nn, dataset[0]);



    nn_save(&nn, "nn_save.txt");
}
