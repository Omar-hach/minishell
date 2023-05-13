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

char	*fill_cmd(char *word, int j, int i)
{
	char	*cmd;

	cmd = (char *)ft_calloc(++i, sizeof(char));
	if (!cmd)
		return (NULL);
	i = -1;
	while ((word[++i] != ' ' && word[i] != '\t') && word[i])
	{
		while (word[i] == 34 || word[i] == 39)
			i++;
		cmd[j] = word[i];
		j++;
	}
	cmd[j] = '\0';
	return (cmd);
}

char	*fill_symb(char *word, int j, int *i)
{
	char	*sym;

	(*i) = -1;
	j = 1;
	if ((word[0] == '>' && word[1] == '>')
		|| (word[0] == '<' && word[1] == '<'))
		j = 2;
	sym = (char *)ft_calloc(j + 1, sizeof(char));
	while (++(*i) < j)
		sym[(*i)] = word[(*i)];
	sym[j] = '\0';
	return (sym);
}

//yassir code

char	*find_path(char *file, int x, int y, int z)
{
	char	*path;
	char	**all_paths;

	all_paths = ft_split(getenv("PATH"), ':');
	path = NULL;
	while (all_paths[++x] && !path)
	{
		y = -1;
		z = -1;
		path = (char *)ft_calloc(ft_strlen(all_paths[x])
				+ ft_strlen(file) + 2, 1);
		while (all_paths[x][++y])
			path[y] = all_paths[x][y];
		path[y++] = '/';
		while (file[++z])
			path[y + z] = file[z];
		path[y + z] = '\0';
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	free_aray(all_paths);
	return (path);
}

//echo "hello    ">a   b   c --> cat a : helo b c
char	*cmd_split(char *word, int *token, t_lexic lex, int type)
{
	int		i;
	int		j;
	char	*cmd;
	char	*arg;
	char	*bin;

	i = 0;
	j = 0;
	word += count_space(word);
	if (*word == '|')
	{
		*token = 21;
		return (NULL);
	}
	while (word[i] != ' ' && word[i] != '\t' && word[i] != '\0')
		i++;
	if (type > 19 || type < 1)
		cmd = fill_cmd(word, j, i);
	if (type < 20 && type > 0)
		cmd = fill_symb(word, j, &i);
	if (!cmd)
		return (NULL);
	bin = find_path(cmd, -1, -1, -1);
	if (ft_find(cmd, lex.l_cmd)
		&& ft_strlen(lex.l_cmd[ft_find(cmd, lex.l_cmd) - 1]) == ft_strlen(cmd)){
		*token = ft_find(cmd, lex.l_cmd) + 10;}
	else if (ft_find(cmd, lex.l_symb) && type < 20) //probleme here
		*token = ft_find(cmd, lex.l_symb) + 20;
	else if (ft_strchr(cmd, '/'))
	{
		*token = 1;
		arg = (char *)ft_calloc(ft_strlen(word) + 1, sizeof(char));
		ft_memcpy(arg, word, ft_strlen(word) + 1);
		ft_printf("token[%p]=%s\n", word, word);
		return (arg);
	}
	else if (bin)
	{
		*token = 1;
		arg = (char *)ft_calloc(ft_strlen(bin) + ft_strlen(word) + 1,
				sizeof(char));
		i = ft_strlen(bin) - ft_strlen(cmd);
		j = -1;
		while (++j < i)
			arg[j] = bin[j];
		ft_memcpy(&arg[j], word, ft_strlen(word) + 1);
		free(cmd);
		free(bin);
		return (arg);
	}
	else
	{
		printf("minshell: %s :command not found\n", cmd);
		free(cmd);
		return (NULL);
	}
	ft_printf("cmd[%d]=%s\n", i, cmd);
	i = ft_strlen(cmd);
	arg = (char *)ft_calloc(ft_strlen(word + i) - count_space(word + i) + 1,
			sizeof(char));
	if (!arg)
		return (NULL);
	word += count_space(word + i) + i;
	i = -1;
	while (word[++i]) //handle arg to **arg with no ""
		arg[i] = word[i];
	arg[i] = '\0';
	free(cmd);
	if (bin)
		free(bin);
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
//	input = detect_exec_var(input); for $VAR
	i = 1;
	words = expr_split(input, lex.l_symb, i);
	if (!words)
		return (free_struct_array(NULL, &lex, NULL, -1));
	*len = nodes_count(words);
	nodes = NULL;
	nodes = malloc_nodes(nodes, *len, &lex);
	if (!fill_nodes(words, &lex, nodes, len))
		return (NULL);
	i = -1;
	while (++i < (*len))
		printf("i =%d type=%d <%s>\n", i, nodes[i].token, nodes[i].arg);
	free_struct_array(words, &lex, NULL, -1);
	return (nodes);
}
//<cmd><|><exp>

int	main(void)
{
	char	*input;
	int		ex;
	t_token	*nodes;
	t_tree	*tree;

	ex = 1;
	tree = NULL;
	nodes = NULL;
	while (ex)
	{
		input = readline(">>> MiniShell $>");
		if (!input)
			break ;
		if (*(input + count_space(input)))
		{
			add_history(input);
			nodes = split_input(input, &ex);
			if (nodes)
			{
				tree = create_tree(nodes, ex);
				treeprint(tree, 0, nodes);
				free_struct_array(NULL, NULL, nodes, ex);
				ex = 1;
			}
		}
		free(input);
		system("leaks minishell");
	}
	exit(1);
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