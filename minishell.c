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

char	*fill_cmd(char *word, int j, int *i)
{
	char	*cmd;
	int		k;

	while ((((word[(*i)] != ' ' && word[(*i)] != '\t'))
		|| !is_outside_quoet(word, *i)) && word[(*i)])
		(*i)++;
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

char	*fill_symb(char *word, int *i, int *token, int type)
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
	char	*arg;

	arg = (char *)ft_calloc(ft_strlen(bin) + ft_strlen(word) + 1, sizeof(char));
	i = ft_strlen(bin) - ft_strlen(cmd);
	j = -1;
	while (++j < i)
		arg[j] = bin[j];
	i = 0;
	while(j <  word[i])
		arg[j++] = word[i++];
	arg[j] = '\0';
	// ft_memcpy(&arg[j], word, ft_strlen(word) + 1);
	return (arg);
}
	// ft_printf("path=%s.  %s\n",  arg, cmd);

char	*set_cmd(char *word, int *token, char *cmd, t_lexic lex)
{
	char	*arg;
	char	*bin;

	//ft_printf("arg = %s , %p ,cmd=%s , %p. word=%s , %p\n", arg, arg, cmd, cmd, word , word);
	if(ft_strncmp(cmd, "..", 2))
		bin = find_path(cmd, -1, -1, -1);
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
		arg = expand_cmd(cmd, bin, word);
		free(bin);
		return (arg);
	}
	if (bin)
		free(bin);
	return (NULL);
}

//handle arg to **arg with no ""
char	*fill_arg(char *word, int i)
{
	char	*arg;
	int		shift;

	arg = (char *)ft_calloc(ft_strlen(word + i) - count_space(word + i) + 1,
			sizeof(char));
	if (!arg)
		return (NULL);
	shift = count_space(word + i) + i;
	word += shift;
	i = -1;
	while (word[++i]) 
		arg[i] = word[i];
	arg[i] = '\0';
	word -= shift;
	return (arg);
}

//echo "hello    ">a   b   c --> cat a : helo b c
char	*cmd_split(char *word, int *token, t_lexic lex)
{
	int		i;
	int		j;
	char	*cmd;
	char	*arg;

	i = 0;
	j = 0;
	cmd = NULL;
	word += count_space(word);
	word = replace_dollars(word);
	ft_printf("word=%s , %p\n", word , word);
	if (ft_find(word, lex.l_symb))
		cmd = fill_symb(word, &i, token, ft_find(word, lex.l_symb));
	else
		cmd = fill_cmd(word, j, &i);
	if (!cmd || *token == 21)
		return (NULL);
	arg = set_cmd(word, token, cmd, lex);
	ft_printf("arg = %s , %p ,cmd=%s , %p. word=%s , %p\n", arg, arg, cmd, cmd, word , word);
	if (*token < 1)
	{
		*error = 127;
		ft_printf("minshell: %s :command not found\n", cmd);
		free(cmd);
		return (NULL);
	}
	if (!arg)
		arg = fill_arg(word, i);
	free(cmd);
	return (arg);
}

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
	*len = nodes_count(words);
	nodes = NULL;
	nodes = malloc_nodes(nodes, *len, &lex);
	if (!fill_nodes(words, &lex, nodes, len))
	{
		*error = 127;
		return (free_struct_array(NULL, &lex, nodes, *len));
	}
	free_struct_array(words, &lex, NULL, -1);
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
	ft_putenv("OLDPWD=");
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
		if (input[count_space(input)])
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
		// system("leaks minishell");
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
				exec_node(tree, nodes);
				free_struct_array(NULL, NULL, nodes, ex);
				ex = 1;
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
