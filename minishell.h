/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:17:17 by ohachami          #+#    #+#             */
/*   Updated: 2023/03/26 23:17:23 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h> 
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h> 
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>
# include <dirent.h>
# include <termios.h> 
# include <termios.h>
# include <curses.h>
# include <term.h>
# include "libft/libft.h"
# include "libft/print/ft_printf.h"

typedef struct s_token
{
	int		token;
	char	*arg;
	char	*in;
	char	*out;
}t_token;

typedef struct s_tree
{
	int				indix;
	struct s_tree	*father;
	struct s_tree	*left_son;
	struct s_tree	*right_son;
}t_tree;

typedef struct s_lexic
{
	char	**l_cmd;
	char	**l_symb;
}t_lexic;

/*
lexixe{
    pape | ::= priority lv.2 --> cmd | cmd
    in derect > >> ::= priority lv.1 -->  cmd > file
    out derect < ::= priority lv.0 --> cmd < file
    $() ::= --> $cmd || $var
    
    << ? 
}
*/
char	**expr_split(char *s, char **sym, int *part);
void	creat_lexic(t_lexic *lex);
int		count_space(char *s);
int		ft_find(char *s, char **token);
int		error_print(char *mes, char *prob, int n);

#endif
