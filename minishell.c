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
char *fill_symb(char *word, int j, int i)//probleme here
{
	char	*sym;

	i = -1;
	j = 1;
	ft_printf("cmd=%s",word);
	if((word[0] == '>' && word[1] == '>') || (word[0] == '<' && word[1] == '<'))
	{
		j = 2;
		sym = (char *)ft_calloc(j + 1, sizeof(char));
	}
	else
		sym = (char *)ft_calloc(j + 1, sizeof(char));
	if(++i < j)
		sym[j] = word[j];
	sym[j] = '\0';
	return (sym);
}
//echo hello > a b c --> cat a : helo b c
char	*cmd_split(char *word, int *token, t_lexic	lex, int type)
{
	int		i;
	int		j;
	char	*arg;
	char	*cmd;

	i = 0;
	j = 0;
	word += count_space(word);
	if(*word == '|')
	{
		*token = 11;
		return (NULL);
	}
	while(word[i] != ' ' && word[i] != '\t' && word[i] != '\0')
		i++;
	if(type < 20)
		cmd = fill_cmd(word, j, i);
	if(type > 19)
		cmd = fill_symb(word, j, i);
	if(!cmd)
		return (NULL);
	if(ft_find(cmd, lex.l_cmd))
		*token = ft_find(cmd, lex.l_cmd) + 10;
	else if(ft_find(cmd, lex.l_symb) && ft_strlen(lex.l_cmd[ft_find(cmd, lex.l_cmd) - 1]) == ft_strlen(cmd))
		*token = ft_find(cmd, lex.l_symb) + 20;
	else if(ft_strchr(cmd, '/'))//maybe put './' in arg ???
		*token = 1;
	else if(type < 20)
	{
		printf("minshell: %s :command not found\n",cmd);
		return (NULL);
	}
	ft_printf("cmd =%s.\n",cmd);
	arg = (char *)ft_calloc(ft_strlen(word + i) - count_space(word + i) + 1, sizeof(char));
	if(!arg)
		return (NULL);
	word += count_space(word + i) + i;
	i = -1;
	while (word[++i])
		arg[i] = word[i];
	arg[i] = '\0';
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
		if(word[i][0] != '>' || word[i][0] != '<')
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
		return (1);
	}
	*len = nodes_count(words);
	nodes = (t_token *)ft_calloc(len, sizeof(t_token));
	if (!nodes)
	{
		free(nodes);
		free(lex.l_cmd);
		free(lex.l_symb);
	}
	i = -1;
	j = 0;
	while(words[++i])
	{
		nodes[j].token = 0;
		nodes[j].arg = cmd_split(words[i], &nodes[j].token, lex,  (j > 0) * nodes[j - 1].token);//should put words[i + 2], 0 , 2 , 4
		ft_printf("i=%d j =%d token=%d\n",i,j,nodes[j].token);
		if (!nodes[i].arg && nodes[j].token != 11)// [0]cmd arg [1]| [2]cmd arg [3]>arg [4]arg2
		{
			free(words);
			free(nodes);
			free(lex.l_cmd);
			free(lex.l_symb);
			return (127);
		}
		if(nodes[j].token > 20)
			nodes[j].arg = ft_strjoin(nodes[j].arg, words[(i++) + 1]);
		j++;
	}
	i = -1;
	while (words[++i])
		printf("--%s--", words[i]);
	printf("\n");
	i = -1;
	while (++i < *len)
		printf("i =%d type=%d <%s>\n",i, nodes[i].token , nodes[i].arg);
	free(nodes);
	free(lex.l_cmd);
	free(lex.l_symb);
	return (0);
}
//<cmd><|><exp>
int	main()
{
	char *input;
	int ex;
	t_token	*nodes;
	t_tree *tree;
	// char **l_cmd;
	// char **l_symb;

	ex = 1;
	tree = NULL;
	nodes = NULL;
	while (ex)
	{
		input = readline(">>> MiniShell $>");
		if (*(input + count_space(input)))
		{
			add_history(input);
			nodes = split_input(input, &ex);
			tree = create_tree(nodes, ex);
			free(nodes);
			free(tree);
		}
		free(input);
	}
	exit(0);
}

//"e""c""h""o" hello need to work,// DONE
// error file name too long > 256
//
