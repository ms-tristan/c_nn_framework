/*
** EPITECH PROJECT, 2024
** maths_functions.c
** File description:
** Theses functions compute on floats.
*/

#include "nn_framework.h"

inline float sigmoidf(float nb)
{
    return 1.f / (1.f + expf(-nb));
}

inline int rand_mm(int min, int max)
{
    return rand() % (max - min) + min;
}
