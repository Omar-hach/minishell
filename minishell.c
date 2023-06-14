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
	int		i;
	t_lexic	lex;
	t_token	*nodes;
	char	**words;

	if (creat_lexic(&lex))
		return (NULL);
	i = 1;
	words = expr_split(input, lex.l_symb, i);
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

void shvlvl()
{
	char	*shlvl;
	char	*shvlv;
	int		vlvl;

	shlvl = getenv("SHLVL");
	vlvl = ft_atoi(shlvl);
	shlvl = ft_itoa(++vlvl);
	shvlv = make_var("SHLVL", shlvl);
	ft_setenv(shvlv);
	ft_setenv("OLDPWD=");
	// free(shvlv);
	free(shlvl);
}

// int	ft_minishell_valgrind()
// {
// 	char	*input;
// 	int		ex;
// 	int fd = open("AAAAA", O_RDONLY);
// 	t_token	*nodes;
// 	t_tree	*tree;

// 	ex = 1;
// 	tree = NULL;
// 	nodes = NULL;
// 	shvlvl();
// 	*g_error = 0;
// 	while (ex)
// 	{
// 		input = get_next_line(fd);
// 		if (!input)
// 			break ;
// 		ft_printf(">>> MiniShell $> %s", input);
// 		if (input[count_space(input)])
// 		{
// 			input[ft_strlen(input) - 1] = '\0';
// 			nodes = split_input(input, &ex);
// 			if (nodes)
// 			{
// 				tree = create_tree(nodes, ex);
// 				//treeprint(tree, 0, nodes);
// 				// ft_printf("\n------EXEC-----\n");
// 				exec_tree(tree, nodes);
// 				free_struct_array(NULL, NULL, nodes, ex - 1);
// 				ex = 1;
// 			}
// 		}
// 		free(input);
// 		// system("leaks minishell");
// 	}
// 	return(*g_error);
// }

int	ft_minishell()
{
	char	*input;
	int		ex;
	t_token	*nodes;
	t_tree	*tree;

	ex = 1;
	tree = NULL;
	nodes = NULL;
	shvlvl();
	*g_error = 0;
	//if(handle_signals())
	//	return(1);
	while (ex)
	{
		input = readline(">>> MiniShell $> ");
		if (!input)
			break ;
		if (input[count_space(input)])
		{
			add_history(input);
			nodes = split_input(input, &ex);
			if (nodes)
			{
				tree = create_tree(nodes, ex);
				// treeprint(tree, 0, nodes);
				// ft_printf("\n------EXEC-----\n");
				exec_tree(tree, nodes);
				free_tree(tree, nodes);
				ex = 1;
			}
		}
		free(input);
		// system("leaks minishell");
	}
	return(*g_error);
}

int	main(int ac, char **av)
{
	char	*in;
	t_token	*nodes;
	t_tree	*tree;
	int		ex;
	int		out;

	ex = 1;
	tree = NULL;
	nodes = NULL;
	g_error = (int *) malloc(1 * sizeof(int));
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		in = av[2];
		if (*(in + count_space(in)))
		{
			shvlvl();
			nodes = split_input(in, &ex);
			if (!nodes)
				return (*g_error);
			if (nodes)
			{
				tree = create_tree(nodes, ex);
				//treeprint(tree, 0, nodes);
				// ft_printf("\n------EXEC-----\n");
				exec_tree(tree, nodes);
				free_tree(tree, nodes);
				// free_struct_array(NULL, NULL, nodes, ex);
				ex = 1;
			}
		}
		return (*g_error);
	}
	else
	{
		ft_minishell();
		out = *g_error;
		free(g_error);
	}
	return (out);
}
//"e""c""h""o" hello need to work,// DONE
// error file name too long > 256
/*
----root=17=arg -->echo
*****branch=21=(null)-->0x6030000028f0
branch=21=(null)-->left=0x0-->right=0x0
root=17=arg -->left=0x0-->right=0x0
branch=21=(null)-->left=echo-->right=0x0
root=17=arg -->left=0x0-->right=0x0
*****branch=13=-->cd
branch=13=-->left=0x0-->right=0x0
root=21=(null)-->left=echo-->right=0x0
branch=13=-->left=0x0-->right=0x0
root=21=(null)-->left=echo-->right=cd
*****branch=21=(null)-->0x603000002950
branch=21=(null)-->left=0x0-->right=0x0
root=13=-->left=0x0-->right=0x0
branch=21=(null)-->left=cd-->right=0x0
root=13=-->left=0x0-->right=0x0
*****branch=11=-->env
branch=11=-->left=0x0-->right=0x0
root=21=(null)-->left=cd-->right=0x0
branch=11=-->left=0x0-->right=0x0
root=21=(null)-->left=cd-->right=env*/
