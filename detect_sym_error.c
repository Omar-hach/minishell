/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   detect_sym_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 23:12:08 by ohachami          #+#    #+#             */
/*   Updated: 2023/05/10 23:12:17 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	last_char(char *s, int queot, int double_qu)
{
	while (*s == ' ' || *s == '\t')
		s--;
	if (queot % 2)
	{
		*g_error = 258;
		ft_printf("minshell: error unexpected token %c\n", 39);
		return (1);
	}
	if (double_qu % 2)
	{
		*g_error = 258;
		ft_printf("minshell: error unexpected token %c\n", 34);
		return (1);
	}
	if (*s == '>' || *s == '|' || *s == '<')
	{
		*g_error = 258;
		ft_printf("minshell: error unexpected token `\\n \n'");
		return (1);
	}
	return (0);
}

int	ftdfdsa(char *s, int queot, int double_qu, char **sym)
{
	s += count_space(s);
	s += ft_strlen(sym[ft_find(s, sym) - 1]);
	queot = (*s == '\'');
	double_qu = (*s == '\"');
	if (ft_find(s, sym) == 1)
	{
		ft_printf("minshell: error unexpected token '%s'",
			sym[ft_find(s, sym) - 1]);
		return (0);
	}
	if (last_char(s + ft_strlen(s) - 1, 0, 0))
		return (0);
	return (0);
}

char	*ft_5(char *s, char **sym, int *part)
{
	int	type;

	type = ft_find(s, sym);
	ft_printf("ok\n");
	if ((type > 1 && ft_find(s, sym) > 0)
		|| (type == 1 && ft_find(s, sym) == 1))
	{
		ft_printf("minshell: error unexpected token '%s'",
			sym[ft_find(s, sym) - 1]);
		return (NULL);
	}
	*part += 2;
	return (s);
}

int	detect_sym_error(char *s, char **sym, int *part)
{
	int	queot;
	int	double_qu;
	int	result;

	result = 0;
	queot = (*s == '\'');
	double_qu = (*s == '\"');
	s = ft_5(s, sym, part);
	if (s == NULL)
		return (0);
	while (*s)
	{
		if ((*s == ';' || *s == '\\') && !(queot % 2) && !(double_qu % 2))
			return (error_print("minshell: error unexpected token", s, 1));
		if (*(s) && ft_find(s, sym) && !(queot % 2) && !(double_qu % 2))
			result = ftdfdsa(s, queot, double_qu, sym);
		queot += (*s == '\'') * !(double_qu % 2);
		double_qu += (*s == '\"') * !(queot % 2);
		s++;
	}
	result += last_char(s - 1, queot, double_qu);
	return (result);
}
