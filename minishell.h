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

typedef struct t_token
{
	int		type;
	char	*arg;
	char	*in;
	char	*out;
} s_token;

typedef struct t_tree
{
	int indix;
	struct t_tree	*father;
	struct t_tree	*left_son;
	struct t_tree	*right_son;
}s_tree;

typedef struct t_lexic
{
	char	**l_cmd;
	char	**l_symb;
}s_lexic;

/*
lexixe{
    pape | ::= priority lv.2 --> cmd | cmd
    in derect > >> ::= priority lv.1 -->  cmd > file
    out derect < ::= priority lv.0 --> cmd < file
    $() ::= --> $cmd || $var
    
    << ? 
}
*/

int     ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *s);


#endif
