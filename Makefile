##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## This is the makefile pof the project
##

FILES 		=	main.c							\
				maths_functions.c 				\
				matrix_computing_functions.c	\
				matrix_management_functions.c	\
				matrix_nn_functions.c			\
				nn_computing_functions.c	 	\
				nn_management_functions.c	 	\
				nn_training_functions.c	 		\
				nn_interactions_functions.c	 	\
				nn_saving_functions.c 			\
				dataset_functions.c 			\
				my_str_to_word_array.c 			\

NAME		= neural_network

all:
	gcc -o $(NAME) $(FILES) -lm -Wextra -Wall
	touch nn_save
	echo "" > nn_save

clean:
	rm -f *~

fclean: clean
	rm -f $(NAME)

re: fclean all
