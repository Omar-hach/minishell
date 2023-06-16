/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:14:18 by ohachami          #+#    #+#             */
/*   Updated: 2023/06/13 21:36:44 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//<cmd><|><exp>
t_token	*split_input(char *input, int *len)
{
	t_lexic	lex;
	t_token	*nodes;
	char	**words;

	if (creat_lexic(&lex))
		return (NULL);
	words = expr_split(input, lex.l_symb);
	if (!words)
	{
		*g_error = 2;
		return (free_struct_array(NULL, &lex, NULL, -1));
	}
	*len = nodes_count(words);
	nodes = NULL;
	nodes = malloc_nodes(nodes, *len, &lex);
	if (!fill_nodes(words, &lex, nodes, len))
	{
		*g_error = 127;
		return (free_struct_array(words, &lex, nodes, *len));
	}
	free_struct_array(words, &lex, NULL, -1);
	return (nodes);
}

void	re_env(void)
{
	extern char	**environ;
	char		**new_env;
	int			x;

	x = 0;
	while (environ[x])
		x++;
	new_env = (char **) ft_calloc((x + 1), sizeof(char *));
	if (!new_env)
		return ;
	x = -1;
	while (environ[++x])
		new_env[x] = ft_strdup(environ[x]);
	new_env[x] = NULL;
	environ = new_env;
}

void	shvlvl(void)
{
	char	*shlvl;
	char	*shvlv;
	int		vlvl;

	re_env();
	shlvl = getenv("SHLVL");
	vlvl = ft_atoi(shlvl);
	shlvl = ft_itoa(++vlvl);
	shvlv = make_var("SHLVL", shlvl);
	ft_setenv(shvlv);
	ft_setenv(ft_strdup("OLDPWD="));
	free(shlvl);
}

// treeprint(tree, 0, nodes);
// ft_printf("\n------EXEC-----\n");
// system("leaks minishell");
int	ft_minishell(t_tree *tree, t_token *nodes)
{
	char	*input;
	int		len;

	while (1)
	{
		input = readline(">>> MiniShell $> ");
		if (!input)
			break ;
		if (input[count_space(input)])
		{
			add_history(input);
			len = 1;
			nodes = split_input(input, &len);
			if (nodes)
			{
				tree = create_tree(nodes, len);
				exec_tree(tree, nodes);
				free_tree(tree, nodes);
				free(nodes);
			}
		}
		free(input);
	}
	return (*g_error);
}

// if(handle_signals())
// 	return(1);
int	main(void)
{
	int		out;
	t_token	*nodes;
	t_tree	*tree;

	g_error = (int *) malloc(1 * sizeof(int));
	*g_error = 0;
	shvlvl();
	tree = NULL;
	nodes = NULL;
	ft_minishell(tree, nodes);
	free_env();
	out = *g_error;
	free(g_error);
	return (out);
}
