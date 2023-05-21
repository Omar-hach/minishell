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
		*error = 258;
		ft_printf("minshell: error unexpected token %c\n", 34);
		return (0);
	}
	if (double_qu % 2)
	{
		*error = 258;
		ft_printf("minshell: error unexpected token %c\n", 39);
		return (0);
	}
	if (*s == '>' || *s == '|' || *s == '<')
	{
		*error = 258;
		ft_printf("minshell: error unexpected token `\\n \n'");
		return (2);
	}
	return (0);
}

int	detect_sym_error(char *s, char **sym, int *part)
{
	int	queot;
	int	double_qu;

	s += count_space(s);
	if (ft_find(s, sym) == 1)
		return (error_print("minshell: error unexpected token",
				sym[ft_find(s, sym) - 1], 2));
	if (last_char(s + ft_strlen(s) - 1, 0, 0))
		return (1);
	queot = (*s == 34);
	double_qu = (*s == 39);
	while (*s)
	{
		queot += (*s == 34) * !(double_qu % 2);
		double_qu += (*s == 39) * !(queot % 2);
		// if (*(++s) && ft_find(s, sym) && !(queot % 2) && !(double_qu % 2))
		if (*(s) && ft_find(s, sym) && !(queot % 2) && !(double_qu % 2))
		{
			queot = ft_find(s, sym);
			s += ft_strlen(sym[ft_find(s, sym) - 1]);
			s += count_space(s);
			if ((queot > 1 && ft_find(s, sym) > 0) || (queot == 1 && ft_find(s, sym) == 1))
			// if (ft_find(s, sym))
				return (error_print("minshell: error unexpected token",
						sym[ft_find(s, sym) - 1], 2));
			queot = 0;
			*part += 2;
		}
		s++;
	}
	return (last_char(s - 1, queot, double_qu));
}
