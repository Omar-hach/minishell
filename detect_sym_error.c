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
		ft_printf("minshell: error unexpected token %c\n", 39);
		return (1);
	}
	if (double_qu % 2)
	{
		*error = 258;
		ft_printf("minshell: error unexpected token %c\n", 34);
		return (1);
	}
	if (*s == '>' || *s == '|' || *s == '<')
	{
		*error = 258;
		ft_printf("minshell: error unexpected token `\\n \n'");
		return (1);
	}
	return (0);
}

int	detect_sym_error(char *s, char **sym, int *part, int type)
{
	int	queot;
	int	double_qu;

	s += count_space(s);
	queot = (*s == '\'');
	double_qu = (*s == '\"');
	if (ft_find(s, sym) == 1)
		return (error_print("minshell: error unexpected token",
				sym[ft_find(s, sym) - 1], 2));
	if (last_char(s + ft_strlen(s) - 1, 0, 0))
		return (1);
	s++;
	//printf("=%s ; %d ; %d\n",s - 1,  queot, double_qu);
	while (*s)
	{
		if ((*s == ';' || *s == '\\') && !(queot % 2) && !(double_qu % 2))
			return (error_print("minshell: error unexpected token", s, 1));
		if (*(s) && ft_find(s, sym) && !(queot % 2) && !(double_qu % 2))
		{
			type = ft_find(s, sym);
			s += ft_strlen(sym[ft_find(s, sym) - 1]);
			s += count_space(s);
			if ((type > 1 && ft_find(s, sym) > 0) || (type == 1 && ft_find(s, sym) == 1))
			// if (ft_find(s, sym))
				return (error_print("minshell: error unexpected token",
						sym[ft_find(s, sym) - 1], 2));
			*part += 2;
		}
		queot += (*s == '\'') * !(double_qu % 2);
		double_qu += (*s == '\"') * !(queot % 2);
		s++;
	}
	//printf("%s ; %d ; %d\n",s - 1 ,  queot, double_qu);
	return (last_char(s - 1, queot, double_qu));
}
