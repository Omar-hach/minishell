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

void	shvlvl(char **env)
{
	char	*shlvl;
	char	*shvlv;
	int		vlvl;
	int		x;

	x = -1;
	while (env[++x])
		env[x] = ft_strdup(env[x]);
	shlvl = getenv("SHLVL");
	if (shlvl)
	{
		vlvl = ft_atoi(shlvl);
		shlvl = ft_itoa(++vlvl);
		shvlv = make_var("SHLVL", shlvl);
		free(shlvl);
		ft_setenv(env, shvlv);
	}
	else
		ft_setenv(env, ft_strdup("SHLVL=1"));
	ft_setenv(env, ft_strdup("OLDPWD="));
}

// treeprint(tree, 0, nodes);
// ft_printf("\n------EXEC-----\n");
// system("leaks minishell");
int	ft_minishell(t_tree *tree, t_token *nodes, char **env)
{
	char	*input;
	int		len;

	while (1)
	{
		input = readline("\033[32m>>> MiniShell $>\033[0m ");
		if (!input)
			break ;
		if (input[count_space(input)])
		{
			add_history(input);
			len = 1;
			nodes = split_input(input, &len);
			free(input);
			if (nodes)
			{
				tree = create_tree(nodes, len);
				exec_tree(tree, nodes, env);
			}
		}
		else
			free(input);
	}
	return (*g_error);
}

int	main(int ac, char **av, char **env)
{
	int		out;
	t_token	*nodes;
	t_tree	*tree;

	(void)(av);
	(void)(ac);
	g_error = (int *) malloc(1 * sizeof(int));
	*g_error = 0;
	shvlvl(env);
	tree = NULL;
	nodes = NULL;
	if (handle_signals())
		return (1);
	ft_minishell(tree, nodes, env);
	free_env(env);
	out = *g_error;
	free(g_error);
	return (out);
}
