/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** This is the main file of the neural network framework.
*/

#include "nn_framework.h"

dat_t *array_to_datasheet(char **array, int ipl, int opl)
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

dat_t **file_to_dataset(int argc, char **argv)
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

nn_t file_to_nn(int argc, char **argv)
{
    int *arch = malloc(sizeof(int) * argc - 2);
    nn_t nn;

    for (int i = 0; i < argc - 2; i++)
        arch[i] = atoi(argv[i + 2]);
    nn = nn_init(arch, argc - 2);
    free(arch);
    return nn;
}

int main(int argc, char **argv)
{
    if (argc < 4) {
        printf("\nUSAGE :\n\n\t./neural_network data_file layer1 layer2 layer3...\n");
        printf("\n\tThe layers are the architecture of the neural network\n");
        printf("\n\tOne line from the datafile is equal to one data sheet :\n");
        printf("\n\tThe inputs length is equal to the first layer's size,\n\tand the output equals to the last one.\n\n");
        return 84;
    }

    srand(time(NULL));

    dat_t **dataset = file_to_dataset(argc, argv);
    nn_t nn = file_to_nn(argc, argv);
    nn_t g = nn_copy_arch(&nn);
    float rate = 1;
    float cost;
    NN_PRINT(nn);

    for (int i = 0; i < 10000; i++) {
        cost  = nn_cost(&nn, dataset);
        printf("[%d]: cost = %f\n", i, cost);
        nn_backprop(&nn, &g, dataset);
        nn_learn(&nn, &g, rate);
    }


    dat_t data_test;
    data_test.intput = mat_init(1, 2);
    data_test.intput.matrix[0][0] = 11;
    data_test.intput.matrix[0][1] = 20;

    nn_print_results(&nn, &data_test);



    nn_free(&nn);
    nn_free(&g);
    dataset_free(dataset);
}

// TODO : ajouter la possibilité de sauvegarder l'état du réseau dans un fichier, et de le rouvrir plus tard
// TODO : ajouter la possibilité de visualiser le réseau (CSFML)
