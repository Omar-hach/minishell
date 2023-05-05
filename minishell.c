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

char *fill_arg(char *word, int j, int i)
{
	char	*arg;

	arg = (char *)ft_calloc(ft_strlen(word + i) - count_space(word + i), sizeof(char));
	if(!arg)
		return (NULL);
	i = -1;
	while ((word[++i] != ' ' && word[i] != '\t') && word[i])
	{
		while (word[i] == 34 || word[i] == 39)
			i++;
		arg[j] = word[i];
		j++;
	}
	arg[j] = '\0';
	return (arg);
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
	while(word[i] != ' ' && word[i] != '\t' && word[i] != '\0')
		i++;
	arg = fill_arg(word, j, i);
	if(!arg)
		return (NULL);
	cmd = (char *)ft_calloc(++i, sizeof(char));
	if(!cmd)
		return (NULL);
	if (!ft_strchr(arg,'/') && ((!ft_find(arg, lex.l_cmd) && type // handle only cmd
		&& (word[i] == ' ' || word[i] == '\t' || !word[i]))
		/*|| ft_strlen(word[ft_find(arg, lex.l_cmd) - 1]) != ft_strlen(cmd)*/))
	{
		printf("bash: %s: command not found\n", cmd);
		free(arg);
		return (NULL);
	}
	if(ft_find(cmd, lex.l_cmd))
		*token = ft_find(cmd, lex.l_cmd) + 10;
	else if(ft_find(cmd, lex.l_symb))
		*token = ft_find(cmd, lex.l_symb) + 20;
	word += count_space(word + i) + i;
	i = -1;
	while (word[++i])
		arg[i] = word[i];
	arg[i] = '\0';
	return (arg);

}

//acess 
int	split_input(char *input)
{
	int		i;
	int 	j;
	int		part;
	t_lexic	lex;
	t_token	*nodes;
	char	**words;

	creat_lexic(&lex);
	part = 1;
//	input = detect_exec_var(input); for $VAR
	words = expr_split(input, lex.l_symb, &part);
	if (!words || !part)
	{
		free(lex.l_cmd);
		free(lex.l_symb);
		return (1);
	}
	nodes = (t_token *)ft_calloc(part / 2 + 1, sizeof(t_token));
	if (!nodes)
	{
		free(nodes);
		free(lex.l_cmd);
		free(lex.l_symb);
	}
	i = -1;
	j = -1;
	while(words[++i])
	{
		nodes[i].token = 0;
		nodes[i].arg = cmd_split(words[i], &nodes[i].token, lex, i/*type*/);//should put words[i + 2], 0 , 2 , 4
		if (!nodes[i].arg)
		{
			free(words);
			free(nodes);
			free(lex.l_cmd);
			free(lex.l_symb);
			return (127);
		}
		if(!i || (words[i][0] == '|'))
		{
		}
	}
	while (words[++i])
		printf("--%s--", words[i]);
	printf("\n");
	i = -1;
	while (++i < part / 2 + 1)
		printf("type=%d<%s>\n", nodes[i].token , nodes[i].arg);
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
	// char **l_cmd;
	// char **l_symb;

	ex = 1;
	while (ex)
	{
		input = readline(">>> MiniShell $>");
		if (*(input + count_space(input)))
		{
			add_history(input);
			split_input(input);
		}
		free(input);
	}
	exit(0);
}

//"e""c""h""o" hello need to work,// DONE
// error file name too long > 256
//
