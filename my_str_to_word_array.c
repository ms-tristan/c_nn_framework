/*
** EPITECH PROJECT, 2023
** my_str_to_word_array.c
** File description:
** This function splits the words of a string into mutiple strings.
*/

#include <stdlib.h>

static int my_isalphanum(char c)
{
    char const list[] = "0123456789";

    for (int i = 0; list[i] != '\0'; i++) {
        if (c == list[i])
            return 1;
    }
    return 0;
}

static int verif_count_word(char const *str, int i, int *on_a_word)
{
    int count = 0;

    if (*on_a_word == 0 && my_isalphanum(str[i]) == 1) {
        count++;
        *on_a_word = 1;
    } else if (my_isalphanum(str[i]) == 0) {
        *on_a_word = 0;
    }
    return count;
}

static int count_words(char const *str)
{
    int count = 0;
    int on_a_word = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        count += verif_count_word(str, i, &on_a_word);
    }
    return count;
}

static int count_next_letters(char const *str, int i)
{
    int count = 0;

    while (my_isalphanum(str[i]) == 0) {
        i++;
    }
    while (my_isalphanum(str[i]) == 1) {
            i++;
            count++;
    }
    return count;
}

static void add_actual_word(char const *str, int actual, char **tab, int i)
{
    int b = 0;

    while (my_isalphanum(str[actual]) == 1) {
        tab[i][b] = str[actual];
        b++;
        actual++;
    }
    tab[i][b] = '\n';
    b++;
    tab[i][b] = '\0';
}

static void add_words(char const *str, char **tab, int words)
{
    int actual = 0;
    int nb_of_letters;
    int i = 0;

    while (i < words) {
        nb_of_letters = count_next_letters(str, actual);
        tab[i] = malloc(sizeof(char) * (nb_of_letters + 2));
        while (my_isalphanum(str[actual]) == 0) {
            actual++;
        }
        add_actual_word(str, actual, tab, i);
        actual += nb_of_letters + 1;
        i++;
    }
    tab[i] = malloc(sizeof(char) * (nb_of_letters + 1));
    i++;
    tab[i] = NULL;
}

char **my_str_to_word_array(char const *str)
{
    int words = count_words(str);
    char **tab = malloc(sizeof(char *) * (words + 2));

    if (str[0] == '\0') {
        tab[0] = NULL;
        return tab;
    }
    add_words(str, tab, words);
    return tab;
}
