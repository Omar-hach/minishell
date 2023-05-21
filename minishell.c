/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:14:18 by ohachami          #+#    #+#             */
/*   Updated: 2023/03/26 23:14:59 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

// char	*fill_cmd(char *word, int j, int i)
// {
// 	char	*cmd;
// 	int		k;

// 	while ((((word[(i)] != ' ' && word[(i)] != '\t')) || !is_outside_quoet(word, i)) && word[(i)])
// 		(i)++;
// 	// ft_printf("i = %d = %d \n", *i, is_outside_quoet(word, *i));
// 	cmd = (char *)ft_calloc((i), sizeof(char));
// 	if (!cmd)
// 		return (NULL);
// 	k = -1;
// 	while (++k < (i))
// 	{
// 		while (word[k] == 34 || word[k] == 39)
// 			k++;
// 		cmd[j] = word[k];
// 		j++;
// 	}
// 	cmd[j] = '\0';
// 	return (cmd);
// }

char	*fill_cmd(char *word, int j, int *i)
{
	char	*cmd;
	int		k;

	while ((((word[(*i)] != ' ' && word[(*i)] != '\t')) || !is_outside_quoet(word, *i)) && word[(*i)])
		(*i)++;
	//ft_printf("i = %d = %d \n", *i, is_outside_quoet(word, *i));
	cmd = (char *)ft_calloc((*i) + 1, sizeof(char));
	if (!cmd)
		return (NULL);
	k = -1;
	while (++k < (*i))
	{
		while (word[k] == 34 || word[k] == 39)
			k++;
		cmd[j] = word[k];
		j++;
	}
	return (cmd);
}

char	*fill_symb(char *word, int *i, int *token,int type)
{
	char	*sym;
	int		j;

	(*i) = -1;
	j = 1;
	if ((word[0] == '>' && word[1] == '>')
		|| (word[0] == '<' && word[1] == '<'))
		j = 2;
	sym = (char *)ft_calloc(j + 1, sizeof(char));
	while (++(*i) < j)
		sym[(*i)] = word[(*i)];
	sym[j] = '\0';
	*token = type + 20;
	return (sym);
}

char	*expand_cmd(char *cmd, char *bin, char *word)
{
	int		i;
	int		j;
	char * arg;

	arg = (char *)ft_calloc(ft_strlen(bin) + ft_strlen(word) + 1, sizeof(char));
	i = ft_strlen(bin) - ft_strlen(cmd);
	j = -1;
	while (++j < i)
		arg[j] = bin[j];
	ft_memcpy(&arg[j], word, ft_strlen(word) + 1);
	free(cmd);
	free(bin);
	return (arg);
}

//echo "hello    ">a   b   c --> cat a : helo b c
char	*cmd_split(char *word, int *token, t_lexic lex)
{
	int		i;
	int		j;
	char	*cmd;
	char	*arg;
	char	*bin;

	i = 0;
	j = 0;
	cmd = NULL;
	word += count_space(word);
	word = replace_dollars(word); //$ management
	if (ft_find(word, lex.l_symb)) //probleme here
		cmd = fill_symb(word, &i, token, ft_find(word, lex.l_symb));
	else
		cmd = fill_cmd(word, j, &i);
	if (!cmd || *token == 21)
		return (NULL);
	if(ft_strncmp(cmd, "..", 2))
		bin = find_path(cmd, -1, -1, -1);
	//token detection
	//ft_printf("word=%d.\n",  *token);
	if (ft_find(cmd, lex.l_cmd)
		&& ft_strlen(lex.l_cmd[ft_find(cmd, lex.l_cmd) - 1]) == ft_strlen(cmd))
		*token = ft_find(cmd, lex.l_cmd) + 10;
	else if (ft_strchr(cmd, '/'))
	{
		*token = 1;
		arg = (char *)ft_calloc(ft_strlen(word) + 1, sizeof(char));
		ft_memcpy(arg, word, ft_strlen(word) + 1);
		return (arg);
	}
	else if (bin)
	{
		*token = 1;
		return (expand_cmd(cmd, bin, word));
	}
	if (*token < 1)
	{
		ft_printf("minshell: %s :command not found\n", cmd);
		*error = 127;
		free(cmd);
		return (NULL);
	}
	//fill arg
	arg = (char *)ft_calloc(ft_strlen(word + i) - count_space(word + i) + 1,
			sizeof(char));
	if (!arg)
	{
		free(cmd);
		return (NULL);
	}
	word += count_space(word + i) + i;
	i = -1;
	while (word[++i]) //handle arg to **arg with no ""
		arg[i] = word[i];
	arg[i] = '\0';
	//free the rest
	free(cmd);
	if (bin)
		free(bin);
	return (arg);
}

// t_token	*split_input(char *input, int *len)
// {
// 	int		i;
// 	t_lexic	lex;
// 	t_token	*nodes;
// 	char	**words;

// 	if (creat_lexic(&lex))
// 		return (NULL);
// 	i = 1;
// 	words = expr_split(input, lex.l_symb, i); // use this for splition the args.
// 	if (!words)
// 		return (free_struct_array(NULL, &lex, NULL, -1));
// 	*len = nodes_count(words);
// 	nodes = NULL;
// 	nodes = malloc_nodes(nodes, *len, &lex);
// 	if (!fill_nodes(words, &lex, nodes, len))
// 		return (NULL);
// 	// i = -1;
// 	// while (++i < (*len))
// 	// 	printf("i =%d type=%d <%s>\n", i, nodes[i].type, nodes[i].arg);
// 	free_struct_array(words, &lex, NULL, -1);
// 	return (nodes);
// }

t_token	*split_input(char *input, int *len)
{
	int		i;
	t_lexic	lex;
	t_token	*nodes;
	char	**words;

	if (creat_lexic(&lex))
		return (NULL);
	i = 1;
	words = expr_split(input, lex.l_symb, i); // use this for splition the args.
	if (!words)
	{
		*error = 2;
		return (free_struct_array(NULL, &lex, NULL, -1));
	}
	// i = -1;
	// printf("\n------------------------------\n");
	*len = nodes_count(words);
	nodes = NULL;
	nodes = malloc_nodes(nodes, *len, &lex);
	// i = -1;
	//  while (words[++i])
	// {
	 	// ft_printf("'%s' ", words[i]);
	if (!fill_nodes(words, &lex, nodes, len))
	{
		// *error = 127;
		return (NULL);
	}
	// i = -1;
	// while (++i < (*len))
	// {
		// printf("i =%d type=%d <%s>\n------------------------------\n", i, nodes[i].type, nodes[i].arg);
	// 	trim_word(nodes[i].arg, nodes[i].type);
	// 	printf("------------------------------\n");
	// }

	// }
	// free_struct_array(words, NULL, NULL, -1);
	return (nodes);
}

//<cmd><|><exp>

void shvlvl()
{
	char	*shlvl;
	int		lvlv;

	shlvl = getenv("SHLVL");
	lvlv = ft_atoi(shlvl);
	lvlv++;
	shlvl = ft_itoa(lvlv); 
	replace_var("SHLVL", shlvl);
	// shlvl = getenv("SHLVL");
	ft_putenv("OLDPWD");
}

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
	*error = 0;
	while (ex)
	{
		input = readline(">>> MiniShell $> ");
		if (!input)
			break ;
		if (*(input + count_space(input)))
		{
			add_history(input);
			nodes = split_input(input, &ex);
			if (nodes)
			{
				tree = create_tree(nodes, ex);
				// treeprint(tree, 0, nodes);
				// ft_printf("\n------EXEC-----\n");
				exec_node(tree, nodes);
				free_struct_array(NULL, NULL, nodes, ex);
				ex = 1;
			}
		}
		// free(input);
		//system("leaks minishell");
	}
	return(*error);
}

int	main(int ac, char **av)
{
	char	*in;
	int		out;
	t_token	*nodes;
	t_tree	*tree;
	int		ex;

	ex = 1;
	tree = NULL;
	nodes = NULL;
	out = 0;
	error = (int *) malloc(1 * sizeof(int));
	if (ac >= 3 && !ft_strncmp(av[1], "-c", 3))
	{
		in = av[2];
		if (*(in + count_space(in)))
		{
			shvlvl();
			nodes = split_input(in, &ex);
			if (!nodes)
				return (*error);
			if (nodes)
			{
				tree = create_tree(nodes, ex);
				//treeprint(tree, 0, nodes);
				// ft_printf("\n------EXEC-----\n");
				out = exec_node(tree, nodes);
				free_struct_array(NULL, NULL, nodes, ex);
				ex = 1;
				*error = out;
			}
		}
		return (*error);
	}
	else
	{
		int exit_status = ft_minishell();
		exit(exit_status);
	}
	return (0);
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
