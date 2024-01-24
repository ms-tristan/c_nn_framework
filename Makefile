##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## This is the makefile pof the project
##

FILES 		=	main.c							\
				maths_functions.c 				\
				matrix_functions.c				\
				matrix_computing_functions.c 	\
				nn_functions.c	 				\
				dataset_functions.c 			\

NAME		= neural_network

all:
	gcc -o $(NAME) $(FILES) -lm -Wextra -Wall

clean:
	rm -f *~

fclean: clean
	rm -f $(NAME)

re: fclean all
