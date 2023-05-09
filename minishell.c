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

char *fill_cmd(char *word, int j, int i)
{
	char	*cmd;

	cmd = (char *)ft_calloc(++i, sizeof(char));
	if(!cmd)
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
char *fill_symb(char *word, int j, int *i)//working fine
{
	char	*sym;

	(*i) = -1;
	j = 1;
	ft_printf("cmd=%s_\n",word);
	if((word[0] == '>' && word[1] == '>') || (word[0] == '<' && word[1] == '<'))
	{
		j = 2;
		sym = (char *)ft_calloc(j + 1, sizeof(char));
	}
	else
		sym = (char *)ft_calloc(j + 1, sizeof(char));
	while(++(*i) < j)
	{
		sym[(*i)] = word[(*i)];}
	sym[j] = '\0';
	return (sym);
}
//yassir code
char	*find_path(char *file)
{
	int		x;
	int		y;
	int		z;
	char	*path;
	char	**all_paths;

	all_paths = ft_split(getenv("PATH"), ':');
	x = -1;
	while (all_paths[++x])
	{
		y = -1;
		z = -1;
		path = (char *)ft_calloc(ft_strlen (all_paths[x]) + ft_strlen (file) + 2, 1);
		while (all_paths[x][++y])
			path[y] = all_paths[x][y];
		path[y++] = '/';
		while (file[++z])
			path[y + z] = file[z];
		path[y + z] = '\0';
		if (access(path, F_OK) == 0)
			return (path);
	}
	return (0);
}

//echo "hello    ">a   b   c --> cat a : helo b c
char	*cmd_split(char *word, int *token, t_lexic	lex, int type)
{
	int		i;
	int		j;
	char	*arg;
	char	*cmd;
	char	*bin;

	i = 0;
	j = 0;
	word += count_space(word);
	if(*word == '|')
	{
		*token = 21;
		return (NULL);
	}
	while(word[i] != ' ' && word[i] != '\t' && word[i] != '\0')
		i++;
	ft_printf("token[%s]=%d\n",word, type);
	if(type > 19 || type < 1)
		cmd = fill_cmd(word, j, i);
	if(type < 20 &&  type > 0)
		cmd = fill_symb(word, j, &i);
	if(!cmd)
		return (NULL);
	bin = find_path(cmd);
	ft_printf("cmd[%d]=%s\n",i,cmd);
	if(ft_find(cmd, lex.l_cmd) && ft_strlen(lex.l_cmd[ft_find(cmd, lex.l_cmd) - 1]) == ft_strlen(cmd))
		*token = ft_find(cmd, lex.l_cmd) + 10;
	else if(ft_find(cmd, lex.l_symb) && type < 20)
		*token = ft_find(cmd, lex.l_symb) + 20;
	else if(ft_strchr(cmd, '/'))
	{
		*token = 1;
		arg = (char *)ft_calloc(ft_strlen(word) + 1, sizeof(char));
		ft_memcpy(arg,word, ft_strlen(word) + 1);
		return (arg);
	}
	else if (bin)
	{
		*token = 1;
		arg = (char *)ft_calloc(ft_strlen(bin) + ft_strlen(word) + 1, sizeof(char));
		i = ft_strlen(bin) - ft_strlen(cmd);
		j = -1;
		while (++j < i)
			arg[j] = bin[j];
		ft_memcpy(&arg[j], word, ft_strlen(word) + 1);
		return (arg);
	}
	else
	{
		printf("minshell: %s :command not found\n",cmd);
		return (NULL);
	}
	i = ft_strlen(cmd);
	arg = (char *)ft_calloc(ft_strlen(word + i) - count_space(word + i) + 1, sizeof(char));
	if(!arg)
		return (NULL);
	word += count_space(word + i) + i;
	i = -1;
	while (word[++i])//handle removing quote and ???
		arg[i] = word[i];
	arg[i] = '\0';
	if (bin)
		free(bin);
	return (arg);
}

int		nodes_count(char **word)
{
	int	i;
	int	part;

	i = -1;
	part = 0;
	while(word[++i])
	{
		printf("'%s' ", word[i]);
		if(word[i][0] != '>' && word[i][0] != '<')
			part++;
	}
	printf("\npart=%d\n",part);
	return (part);
}
//acess 
t_token	*split_input(char *input,int *len)
{
	int		i;
	int 	j;
	int		k;
	t_lexic	lex;
	t_token	*nodes;
	char	**words;

	creat_lexic(&lex);
//	input = detect_exec_var(input); for $VAR
	i = 1;
	words = expr_split(input, lex.l_symb, i);
	if (!words)
	{
		free(lex.l_cmd);
		free(lex.l_symb);
		return (NULL);
	}
	*len = nodes_count(words);
	nodes = (t_token *)ft_calloc(*len, sizeof(t_token));
	if (!nodes)
	{
		free(nodes);
		free(lex.l_cmd);
		free(lex.l_symb);
		return (NULL);
	}
	i = -1;
	j = 0;
	k = 0;
	while(words[++i])
	{
		nodes[j].token = 0;
		nodes[j].arg = cmd_split(words[i], &nodes[j].token, lex,  (j > 0) * nodes[j - 1].token);//should put words[i + 2], 0 , 2 , 4
		ft_printf("i=%d j =%d k=%d token=%d\n", i, j, k, nodes[j].token);
		if (!nodes[i].arg && nodes[j].token == 0)// [0]cmd arg [1]| [2]cmd arg [3]>arg [4]arg2
		{
			i = -1;
			while(words[++i])
				free(words[i]);
			free(words);
			i = -1;
			while(++i < (*len - 1))
				free(nodes[i].arg);
			free(nodes);
			free(lex.l_cmd);
			free(lex.l_symb);
			return (NULL);//127
		}
		if(nodes[j].token > 21)
			nodes[k].arg = ft_strjoin(nodes[k].arg, words[(i++) + 1]);
		if(nodes[j].token == 21)
			k = i;
		j++;
	}
	i = -1;
	while (++i < *len)
		printf("i =%d type=%d <%s>\n",i, nodes[i].token , nodes[i].arg);
	i = -1;
	while(words[++i])
		free(words[i]);
	free(words);
	free(lex.l_cmd);
	free(lex.l_symb);
	return (nodes);
}
//<cmd><|><exp>

void treeprint(t_tree *root, int level,t_token *nodes)
{
	int i =7;

    if (root == NULL)
        return;
	level += 8;
    treeprint(root->right_son, level, nodes);
	ft_printf("\n");
    while (++i < level)
	{
        ft_printf(" ");
	}
	ft_printf("%d=%s-->left=%p-->right=%p\n", nodes[root->indix].token,nodes[root->indix].arg, root->left_son, root->right_son);
    treeprint(root->left_son, level, nodes);
}

int	main()
{
	char	*input;
	int		ex;
	t_token	*nodes;
	//t_tree *tree;
	// char **l_cmd;
	// char **l_symb;

	ex = 1;
	//tree = NULL;
	nodes = NULL;
	while (ex)
	{
		input = readline(">>> MiniShell $>");
		if(!input)
			break;
		ft_printf("ex=%d\n",ARG_MAX);
		if (*(input + count_space(input)))
		{
			add_history(input);
			nodes = split_input(input, &ex);
			/*if(nodes)
			{
				tree = create_tree(nodes, ex);
				treeprint(tree, 0, nodes);
				free(tree);
			}*/
			if(nodes)
			{
				while(-1 < --ex)
					free(nodes[ex].arg);
				free(nodes);
				ex = 1;
			}
		}
		free(input);
	}
	exit(0);
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