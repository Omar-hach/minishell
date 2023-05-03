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

char **alloc_array(char *word, int j, int *i)
{
	char	**array;

	word += count_space(word);
	array = (char **)ft_calloc(3, sizeof(char *));
	if(!array)
		return (NULL);
	while(word[*i] != ' ' && word[*i] != '\t' && word[*i] != '\0')
		(*i)++;
	(*i)++;
	array[0] = (char *)ft_calloc(*i, sizeof(char));
	array[1] = (char *)ft_calloc(ft_strlen(word + (*i)) - count_space(word + (*i)), sizeof(char)); 
	array[2] = NULL;
	*i = -1;
	while ((word[++(*i)] != ' ' && word[*i] != '\t') && word[*i])
	{
		while (word[*i] == 34 || word[*i] == 39)
			(*i)++;
		array[0][j] = word[*i];
		j++;
	}
	array[0][j] = '\0';
	return (array);
}
//echo hello > a b c --> cat a : helo b c
char	**cmd_split(char *word, char **cmd)
{
	int		i;
	int		j;
	char	**array;

	j = 0;
	i = 0;
	array = alloc_array(word, j, &i);
	if(!array)
		return (NULL);
	if (!ft_strchr(array[0],'/') && ((!ft_find(array[0], cmd) 
		&& (word[i] == ' ' || word[i] == '\t' || !word[i]))
		|| ft_strlen(cmd[ft_find(array[0], cmd) - 1]) != ft_strlen(array[0])))
	{
		printf("bash: %s: command not found\n", array[0]);
		free(array);
		return (NULL);
	}
	word += count_space(word + i) + i;
	i = -1;
	while (word[++i])
		array[1][i] = word[i];
	array[1][i] = '\0';
	return (array);

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
	nodes = (t_token	*)ft_calloc(part / 2 + 1, sizeof(t_token));
	if (!nodes)
	{
		free(nodes);
		free(lex.l_cmd);
		free(lex.l_symb);
	}
	i = -1;
	j = -1;
	nodes[0].arg = cmd_split(words[0], nodes[0].arg, lex.l_cmd);
	while(words[++i])
	{
		if(!i || (words[i][0] == '|'))
		{
			nodes[i].arg[i] = cmd_split(words[(i + 1) * (i > 0)], lex.l_cmd);//should put words[i + 2], 0 , 2 , 4
			if (!cmd[j])
			{
				free(words);
				free(lex.l_cmd);
				free(lex.l_symb);
				return (127);
			}
		}
	}
	while (words[++i])
		printf("--%s--", words[i]);
	printf("\n");
	while (cmd && cmd[++i])
		printf("<%s>\n", cmd[i]);
	free(cmd);
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
