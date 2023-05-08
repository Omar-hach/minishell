/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 07:46:06 by ohachami          #+#    #+#             */
/*   Updated: 2023/04/25 07:46:08 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	creat_lexic(t_lexic *lex)
{
	lex->l_cmd = (char **)malloc(8 * sizeof(char *));
	if (!lex->l_cmd)
		exit(1);
	lex->l_cmd[0] = "env";//11
	lex->l_cmd[1] = "pwd";
	lex->l_cmd[2] = "cd";
	lex->l_cmd[3] = "exit";
	lex->l_cmd[4] = "export";
	lex->l_cmd[5] = "unset";
	lex->l_cmd[6] = "echo";//17
	lex->l_cmd[7] = NULL;
	lex->l_symb = (char **)malloc(6 * sizeof(char *));
	if (!lex->l_cmd)
	{
		free(lex->l_cmd);
		exit(1);
	}
	lex->l_symb[0] = "|";//21
	lex->l_symb[1] = ">>";
	lex->l_symb[2] = ">";
	lex->l_symb[3] = "<<";
	lex->l_symb[4] = "<";//25
	lex->l_symb[5] = NULL;
}

int	count_space(char *s)
{
	int	i;

	if(!s)
		return (0);
	i = 0;
	while (s[i] && ((s[i] == ' ') || (s[i] == '\t')))
		i++;
	return (i);
}

int	ft_find(char *s, char **token)
{
	int	i;
	int	diff;

	i = -1;
	diff = 0;
	while (token[++i])
	{
		diff = ft_strncmp(token[i], s, ft_strlen(token[i]));
		if (!diff)
			return (i + 1);
	}
	return (0);
}

int	error_print(char *message, char *prob, int n)
{
	printf("%s '", message);
	while (*prob && n--)
	{
		printf("%c", *prob);
		prob++;
	}
	printf("'\n");
	return (1);
}
