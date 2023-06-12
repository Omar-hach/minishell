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
# include <limits.h>
# include "libft/libft.h"
# include "libft/print/ft_printf.h"
# include <errno.h>
# include <string.h>

typedef struct s_token
{
	int		type;
	// char	*arg;
	char	**args;
	int		qt;
}t_token;

typedef struct s_tree
{
	int				token_index;
	struct s_tree	*father;
	struct s_tree	*left_son;
	struct s_tree	*right_son;
}t_tree;

typedef struct s_lexic
{
	char	**l_cmd;
	char	**l_symb;
}t_lexic;

int		*g_error;

/*
lexixe{
	 pape | ::= priority lv.2 --> cmd | cmd
	 in derect > >> ::= priority lv.1 -->  cmd > file
	 out derect < ::= priority lv.0 --> cmd < file
	 $() ::= --> $cmd || $var
	 << ? 
}
*/

int		fork1(void);
int		ft_dup(int fd, int new_fd);
char	*get_path(char **all_paths, char *file, int x);
char	*find_path(char *file);
int		check_file(char *file);

char	**arg_split(char *s, char *c);
void	ft_skip(t_token *tokens, int i);
int		is_quote_skip(char c, int *qt, int *dualqt, int *qted);

int		is_varname(char *var);
int		is_var(char *var);
int		ft_findvar(char *var);
void	ft_putenv(char *var);
void	ft_unputenv(char *name);
int		replace_var(char *var, char *value);

char	*get_dollar_name(char *s, int x, int z);
int		is_money_end(char c);
char	*is_money(char *s, int *x, int qt, int dualqt);
char	*mint_dollars(char *s, int start, int name_len, char *val);
char	*get_dollars(char *s, int *x, int qt);
char	*replace_dollars(char *s);

int		here_doc(char *s, int qt);
int		here_file(char *s, int qt);
int		here_file(char *s, int qt);
int		make_heredocs(t_tree *tree, t_token *tokens);
int		remove_heredocs(t_tree *tree, t_token *tokens);

int		change_oldpwd(void);
char	*extra_cd(char *path);
int		ft_cd(int ac, char **av);
int		ft_echo(int ac, char **av);
int		ft_pwd(void);
int		ft_pipe(t_tree *tree, t_token *tokens);
int		ft_env_declare(void);

int		exec_tree(t_tree *tree, t_token *tokens);
int		exec_node(t_tree *tree, t_token *tokens);
int		exec_token(t_tree *tree, t_token *tokens);
int		exec_redir(t_tree *tree, t_token *tokens);
int		exec_cmd(t_token token);
int		exec_symbol(t_tree *tree, t_token *tokens);

int		is_outside_quoet(char *s, int end);
char	**trim_word(char *words, int type);
char	**expr_split(char *s, char **sym, int parct);
int		creat_lexic(t_lexic *lex);
int		count_space(char *s);
int		ft_find(char *s, char **token);
int		error_print(char *mes, char *prob, int n);
t_tree	*create_tree(t_token *nodes, int len);
int		detect_sym_error(char *s, char **sym, int *part, int type);
void	*free_aray(char	**words);
t_token	*malloc_nodes(t_token *nodes, int len, t_lexic *lex);
void	*free_struct_array(char **words, t_lexic *lex, t_token *nodes, int len);
int		nodes_count(char **word);
t_token	*fill_nodes(char **words, t_lexic *lex, t_token *nodes, int *len);
char	*cmd_split(char *word, int *token, t_lexic lex);
void	free_tree(t_tree *root);
void	treeprint(t_tree *root, int level, t_token *nodes);

#endif
