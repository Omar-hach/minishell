/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbole_parcing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 07:46:34 by ohachami          #+#    #+#             */
/*   Updated: 2023/04/25 07:46:36 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int	last_char(char *s, int queot, int double_qu)
{
//	int	i;

	while (*s == ' ' || *s == '\t')
		s--;
	if (*s == '>' || *s == '|' || *s == '$' || *s == '<')
	{
		printf("minshell: error unexpected token `%c'\n", *s);
		return (1);
	}
	if (queot % 2)
	{
		printf("minshell: error unexpected token %c\n", (queot % 2) * 34);
		return (1);
	}
	if (double_qu % 2)
	{
		printf("minshell: error unexpected token %c\n",
			(double_qu % 2) * 39);
		return (1);
	}
	return (0);
}
//"l""s"'|'"gre""p" a --> zsh: command not found: ls|grep

int	detect_sym_error(char *s, char **sym, int *part)
{
	int	queot;
	int	double_qu;

	queot = 0;
	double_qu = 0;
	while (*s)
	{
		queot += (*s == 34);
		double_qu += (*s == 39);
		if ((*s == ';' || *s == 92) && !(queot % 2) && !(double_qu % 2))
			return (error_print("minshell: error unexpected token", s, 1));
		s++;
		if (*s && ft_find(s, sym) && !(queot % 2) && !(double_qu % 2))
		{
			s += ft_strlen(sym[ft_find(s, sym) - 1]);
			s += count_space(s);
			if (ft_find(s, sym))
				return (error_print("minshell: error unexpected token",
						sym[ft_find(s, sym) - 1],
						ft_strlen(sym[ft_find(s, sym) - 1])));
			*part += 2;
		}
	}
	return (last_char(s - 1, queot, double_qu));
}

int	*word_len(char *s, char **sym, int part)
{
	int	*array;
	int	i;
	int	queot;
	int	double_qu;

	array = (int *)ft_calloc(part, sizeof(int));
	if (!array)
		return (NULL);
	i = 0;
	queot = 0;
	double_qu = 0;
	while (*s && i < part)
	{
		array[i] = 1;
		queot += (*s == 34);
		double_qu += (*s == 39);
		while (*(++s) && !ft_find(s, sym) && !(queot % 2 || double_qu % 2))
			array[i]++;
		ft_printf("array[%d] = %d\n",i,array[i]);
		s+= count_space(s);
		if (ft_find(s, sym) && !(queot % 2 || double_qu % 2) && ++i < part)
			array[i] = ft_strlen(sym[ft_find(s, sym) - 1]);
		if(i < part)
			s+= array[i++];
		ft_printf("ok\n");
	}
	return (array);
}

char	**word_cutter(char *s, int *len_array, char **array)
{
	int		i;
	int		l;
	int		j;
	int		k;

	l = len_array[0];
	i = 0;
	j = -1;
	k = -1;
	while (s[++k])
	{
		array[i][++j] = s[k];
		ft_printf("<%c\\/%s> l = %d > %d = k\n",array[i][j], s + k, l, k);
		if (--len_array[i] < 1)
		{
			array[i][++j] = '\0';
			ft_printf("-%s-\n",array[i]);
			i++;
			j = -1;
			l += len_array[i] + 1;
		}
	}
	return (array);
}

char	**expr_split(char *s, char **sym)
{
	char	**array;
	int		*len_array;
	int		part;
	int		i;

	array = NULL;
	part = 1;
	if (detect_sym_error(s, sym, &part))
		return (NULL);
	array = (char **)ft_calloc(part + 1, sizeof(char *));
	if (!array)
		return (NULL);
	len_array = word_len(s, sym, part);
	if (!len_array)
	{
		free(array);
		return (NULL);
	}
	i = -1;
	while (++i < part)
		array[i] = (char *)ft_calloc(len_array[i] + 1, sizeof(char));
	ft_printf("<%s>\n", s);
	array = word_cutter(s, len_array, array);
	array[part ] = NULL;
	free(len_array);
	return (array);
}

