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
		printf("minshell: error unexpected token %c\n", 34);
		return (1);
	}
	if (double_qu % 2)
	{
		printf("minshell: error unexpected token %c\n", 39);
		return (1);
	}
	if (*s == '>' || *s == '|' || *s == '<')
	{
		printf("minshell: error unexpected token `%c", *s);
		if ((*(s - 1) == '>' && *s == '>') || (*(s - 1) == '>' && *s == '>'))
			printf("%c", *(s - 1));
		printf("'\n");
		return (1);
	}
	return (0);
}

int	detect_sym_error(char *s, char **sym, int *part)
{
	int	queot;
	int	double_qu;

	queot = 0;
	double_qu = 0;
	if (ft_find(s + count_space(s), sym))
		return (error_print("minshell: error unexpected token",
				sym[ft_find(s, sym) - 1], 2));
	while (*s)
	{
		queot += (*s == 34) * !(double_qu % 2);
		double_qu += (*s == 39) * !(queot % 2);
		if ((*s == ';' || *s == 92) && !(queot % 2) && !(double_qu % 2))
			return (error_print("minshell: error unexpected token", s, 1));
		if (*(++s) && ft_find(s, sym) && !(queot % 2) && !(double_qu % 2))
		{
			s += ft_strlen(sym[ft_find(s, sym) - 1]);
			s += count_space(s);
			if (ft_find(s, sym))
				return (error_print("minshell: error unexpected token",
						sym[ft_find(s, sym) - 1], 2));
			*part += 2;
		}
	}
	return (last_char(s - 1, queot, double_qu));
}
