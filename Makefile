# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/26 23:26:53 by ohachami          #+#    #+#              #
#    Updated: 2023/06/13 21:36:24 by yhachami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

HEADER = minishell.h

CFLAGS = -Werror -Wall -Wextra -I/Users/ohachami/.brew/opt/readline/include

FLAGS = -lreadline -lcurses -L/Users/ohachami/.brew/opt/readline/lib

SRC = 	minishell.c \
		symbole_parcing.c nodes_utils.c cmd_split.c\
		detect_sym_error.c create_tree.c\
		utils_o.c utils_free.c utils_arg.c\
		exec_tree.c symbol.c commands.c dollars.c heredoc.c\
		ft_cd.c ft_echo.c ft_pipe.c arg_split.c path_finder.c\
		utils_y.c  utils_var.c utils_check.c utils_env.c\
		signal_handling.c

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

all:$(NAME)

$(NAME): $(OBJ) $(HEADER)
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
