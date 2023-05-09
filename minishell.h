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

// # define PATH_MAX 32000

typedef struct s_token
{
	int	type;
	char	*arg;
	int	in;
	int	out;
}t_token;

typedef struct s_tree
{
	int	token_index;
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

int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_strlen(const char *s);
char		*ft_strdup(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_isalnum(int c);
char		*ft_strjoin(char const *s1, char const *s2);
char		**ft_split(char const *s, char c);
void		*ft_calloc(size_t count, size_t size);
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);

char		*ft_strdup_newline(char *s);
char		*join_args(char **args, char between);
int		fork1();
int		ft_dup(int fd, int new_fd);
char		*find_path(char *file);

int 		ft_isvar(char *var);
int		ft_findvar(char *var);
void		ft_putenv(char *var);
void		ft_unputenv(char *name);
int		replace_var(char *var, char *value);

char		*replace_dollars(char *s);

int		exec_cmd(t_token token);
int		exec_symbol(t_tree *tree, t_token *tokens);
int		exec_node(t_tree *tree, t_token *tokens);

char	**expr_split(char *s, char **sym, int part);
void	creat_lexic(t_lexic *lex);
int		count_space(char *s);
int		ft_find(char *s, char **token);
int		error_print(char *mes, char *prob, int n);
t_tree *create_tree(t_token *nodes, int len);


#endif
