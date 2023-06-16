/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_o.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 07:46:06 by ohachami          #+#    #+#             */
/*   Updated: 2023/04/25 07:46:08 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

//echo = 17
// |  = 21
int	creat_lexic(t_lexic *lex)
{
	lex->l_cmd = (char **)malloc(8 * sizeof(char *));
	if (!lex->l_cmd)
		return (1);
	lex->l_cmd[0] = ft_strdup("env");
	lex->l_cmd[1] = ft_strdup("pwd");
	lex->l_cmd[2] = ft_strdup("cd");
	lex->l_cmd[3] = ft_strdup("exit");
	lex->l_cmd[4] = ft_strdup("export");
	lex->l_cmd[5] = ft_strdup("unset");
	lex->l_cmd[6] = ft_strdup("echo");
	lex->l_cmd[7] = NULL;
	lex->l_symb = (char **)malloc(6 * sizeof(char *));
	if (!lex->l_cmd)
	{
		free_aray(lex->l_cmd);
		return (1);
	}
	lex->l_symb[0] = ft_strdup("|");
	lex->l_symb[1] = ft_strdup("<<");
	lex->l_symb[2] = ft_strdup("<");
	lex->l_symb[3] = ft_strdup(">>");
	lex->l_symb[4] = ft_strdup(">");
	lex->l_symb[5] = NULL;
	return (0);
}

int	count_space(char *s)
{
	int	i;

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
	while (token && token[++i])
	{
		diff = ft_strncmp(token[i], s, ft_strlen(token[i]));
		if (!diff)
			return (i + 1);
	}
	return (0);
}

int	error_print(char *message, char *prob, int n, int error)
{
	if (!error)
		*g_error = 258;
	else
		*g_error = error;
	ft_printf("%s '", message);
	while (*prob && n--)
	{
		ft_printf("%c", *prob);
		prob++;
	}
	ft_printf("'\n");
	return (1);
}

int	is_outside_quotes(char *s, int end)
{
	int	i;
	int	queot;
	int	double_qu;

	queot = 0;
	double_qu = 0;
	i = -1;
	while (s[++i] && i <= end)
	{
		queot += (s[i] == '\'') * !(double_qu % 2);
		double_qu += (s[i] == '\"') * !(queot % 2);
	}
	return (!(queot % 2) && !(double_qu % 2));
}
