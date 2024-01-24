/*
** EPITECH PROJECT, 2024
** main.c
** File description:
** This is the main file of the neural network framework.
*/

#include "nn_framework.h"

int main(int argc, char **argv)
{
    int dot_and_sum_arch[] = {2, 4, 4, 1};
    nn_t nn = NN_INIT(dot_and_sum_arch);

    // nn_rand(&nn);
    NN_PRINT(nn);
}
    // nn_t nn = NN_INIT(tset_arch);
    // nn_rand(&nn);

    // NN_PRINT(nn);

    // nn_t xor_nn = NN_INIT(xor_arch);
    // nn_rand(&xor_nn);
    // NN_PRINT(xor_nn);
// TODO : ajouter la possibilité de rentrer un fichier en paramètre pour le parse et s'en servir de training data
// TODO : ajouter la possibilité de créer son propre réseau 100% en passant l'architecture en arguments du programme
// TODO : ajouter la possibilité de sauvegarder l'état du réseau dans un fichier, et de le rouvrir plus tard
// TODO : ajouter la possibilité de visualiser le réseau (CSFML)
