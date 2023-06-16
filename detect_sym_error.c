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

int	last_char(char *s, int i)
{
	int	queot;
	int	double_qu;
	int	j;

	queot = (s[0] == '\'');
	double_qu = (s[0] == '\"');
	j = 0;
	while (s[++j])
	{
		queot += (s[j] == '\'') * !(double_qu % 2);
		double_qu += (s[j] == '\"') * !(queot % 2);
	}
	if (queot % 2)
		return (error_print("minshell: error unexpected token", "\'", 1, 1));
	if (double_qu % 2)
		return (error_print("minshell: error unexpected token", "\"", 1, 1));
	while (s[i] == ' ' || s[i] == '\t')
		i--;
	if (s[i] == '>' || s[i] == '|' || s[i] == '<')
		return (error_print("minshell: error unexpected token", "\\n", 2, 2));
	return (0);
}

int	detect_sym_error(char *s, char **sym, int *part, int type)
{
	int	i;

	i = count_space(s);
	if (ft_find(s + i, sym) == 1)
		return (error_print("minshell: error unexpected token",
				sym[ft_find(s + i, sym) - 1], 2, 130));
	if (last_char(s, ft_strlen(s) - 1))
		return (1);
	while (s[++i])
	{
		if ((s[i] == ';' || s[i] == '\\') && is_outside_quotes(s, i))
			return (error_print("minshell: error unexpected token", s, 1, 2));
		if (s[i] && ft_find(s + i, sym) && is_outside_quotes(s, i))
		{
			type = ft_find(s + i, sym);
			i += ft_strlen(sym[ft_find(s + i, sym) - 1]);
			i += count_space(s);
			if ((type > 1 && ft_find(s + i, sym) > 0)
				|| (type == 1 && ft_find(s + i, sym) == 1))
				return (error_print("minshell: error unexpected token",
						sym[ft_find(s + i, sym) - 1], 2, 1));
			*part += 2;
		}
	}
	return (last_char(s, i - 1));
}
