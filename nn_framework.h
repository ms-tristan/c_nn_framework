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
#include <time.h>

#define MAT_PRINT(m) mat_print(m, #m)
#define NN_PRINT(nn) nn_print(nn, #nn)
#define NN_INIT(arch) nn_init(arch, (int)(sizeof(arch) / sizeof(*arch)))
#define DATASHEET_INIT(ip, op) datasheet_init(ip, (int)(sizeof(ip) / sizeof(*ip)), op, (int)(sizeof(op) / sizeof(*op)))

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
    int inputs_len;
    float *inputs;
    int outputs_len;
    float *expected_outputs;
    struct data *next;
} dat_t;

// MATHS FUNCTIONS
float sigmoidf(float nb);
int rand_mm(int min, int max);

// MATRIX FUNCTIONS
mat_t mat_init(int rows, int cols);
void mat_rand(mat_t *m);
void mat_copy(mat_t *dest, mat_t *src);
void mat_print(mat_t m, const char *name);
void mat_set(mat_t *m, int nb);
void mat_sig(mat_t *m);
void mat_dot(mat_t *dest, mat_t *src1, mat_t *src2);
void mat_sum(mat_t *dest, mat_t *src);
void mat_free(mat_t *m);

// NEURAL NETWORK FUNCTIONS
nn_t nn_init(int *arch, int arch_size);
void nn_rand(nn_t *nn);
void nn_forward(nn_t *nn, dat_t *td);
void nn_backward(nn_t *nn, nn_t *g, dat_t td);
void nn_print(nn_t nn, const char *name);
void nn_free(nn_t *nn);

// DATA FUNCTIONS
dat_t datasheet_init(float *inputs, int ip_len, float *outputs, int op_len);
void dataset_append(dat_t **dataset, dat_t *datasheet);
void dataset_print(dat_t *dataset);
