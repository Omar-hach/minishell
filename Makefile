# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/26 23:26:53 by ohachami          #+#    #+#              #
#    Updated: 2023/03/26 23:29:20 by ohachami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc 

CFLAGS = -Werror -Wall -Wextra 

FLAGS = -lreadline -lcurses -fsanitize=address

SRC = 	ft_utils.c\
		symbole_parcing.c\
		minishell.c 

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

all:$(NAME)

$(NAME):$(OBJ)
	make -C libft
	$(CC) $(FLAGS) $(OBJ) $(LIBFT) -o $(NAME) 

clean:
	make -C libft clean
	rm -f *.o libft/*.o get_next_line/*.o print/*.o

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all
	make -C libft re

.PHONY: all clean fclean re
