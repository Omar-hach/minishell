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

# include <limits.h>

typedef struct s_token
{
	int		token;
	char	*arg;
	int		redir;
	char	*out;
}t_token;

// echo hey 26h2g61h | ls

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
    $ ::= --> $cmd || $var
    
    << ? 
}
*/
int		error;

int		is_outside_quoet(char *s, int end);
char	**expr_split(char *s, char **sym, int part);
int		creat_lexic(t_lexic *lex);
int		count_space(char *s);
int		ft_find(char *s, char **token);
int		error_print(char *mes, char *prob, int n);
t_tree	*create_tree(t_token *nodes, int len);
int		detect_sym_error(char *s, char **sym, int *part);
void	*free_aray(char	**words);
t_token	*malloc_nodes(t_token *nodes, int len, t_lexic *lex);
void	*free_struct_array(char **words, t_lexic *lex, t_token *nodes,  int len);
int		nodes_count(char **word);
t_token	*fill_nodes(char **words, t_lexic *lex, t_token *nodes, int *len);
char	*cmd_split(char *word, int *token, t_lexic lex, int type);
int		detect_sym_error(char *s, char **sym, int *part);
char	*replace_dollars(char *s);
char	**trim_word(char *words, int type);

void	treeprint(t_tree *root, int level, t_token *nodes);

#endif
