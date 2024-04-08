/*
** EPITECH PROJECT, 2024
** nn_framework.h
** File description:
** This is th header file of the neural network framework.
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <fcntl.h>
#include <time.h>

// MACROS
#define MAT_PRINT(m) mat_print(m, #m)
#define NN_PRINT(nn) nn_print(nn, #nn)
#define NN_INIT(arch) nn_init(arch, (int)(sizeof(arch) / sizeof(*arch)))

#define ACTIVATION SIGF

typedef enum activation_func {
    SIGF,
    DIV,
    NONE
} activ_e;

typedef struct vector3i {
    int x;
    int y;
    int z;
} vec3i_t;

typedef struct matrix {
    int rows;
    int cols;
    float **matrix;
} mat_t;

typedef struct neural_network {
    int arch_size;
    mat_t *weights;
    mat_t *bias;
    mat_t *nodes;
} nn_t;

typedef struct data {
    mat_t intput;
    mat_t output;
    struct data *next;
} dat_t;

// MATHS FUNCTIONS
float sigmoidf(float nb);
int rand_mm(int min, int max);
float activation(float nb, activ_e act);

// MATRIX FUNCTIONS
mat_t mat_init(int rows, int cols);
void mat_rand(mat_t *m);
void mat_copy(mat_t *dest, mat_t *src);
void mat_print(mat_t m, const char *name);
void mat_set(mat_t *m, int nb);
void mat_act(mat_t *m, activ_e act);
void mat_dot(mat_t *dest, mat_t *src1, mat_t *src2);
void mat_sum(mat_t *dest, mat_t *src);
void mat_free(mat_t *m);
void mat_div(mat_t *m, int div);
void mat_substract(mat_t *dest, mat_t *src);
void mat_mutate(mat_t *mat, float mutation_rate);

// NEURAL NETWORK FUNCTIONS
nn_t nn_init(int *arch, int arch_size);
nn_t nn_copy_arch(nn_t *nn);
nn_t nn_open(const char *path);
void nn_copy(nn_t *dest, nn_t *src);
void nn_rand(nn_t *nn);
void nn_forward(nn_t *nn, dat_t *td);
void nn_train(nn_t *nn, nn_t *g, dat_t **dataset);
void nn_print(nn_t nn, const char *name);
void nn_free(nn_t *nn);
void nn_set(nn_t *nn, float nb);
float nn_cost(nn_t *nn, dat_t **dataset);
void nn_apply_gradient(nn_t *nn, nn_t *g, float rate);
void nn_print_results(nn_t *nn, dat_t *td);
void nn_mutate(nn_t *nn, float mutation_rate);
void nn_save(nn_t *nn, const char *path);

// DATA FUNCTIONS
dat_t *datasheet_init(float *inputs, int ip_len, float *outputs, int op_len);
void dataset_append(dat_t **dataset, dat_t *datasheet);
void dataset_print(dat_t **dt);
void dataset_free(dat_t **dataset);

// OTHER
char **my_str_to_word_array(char const *str);
