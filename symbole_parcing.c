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
	if (*s == '>' || *s == '|' || *s == '<')//need to fix this for << AND >>
	{
		printf("minshell: error unexpected token `%c'\n", *s);
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

int	get_symb_len(int sym_type, char *s, char **sym)
{
	int	queot;
	int	double_qu;
	int	count;

	queot = 0;
	double_qu = 0;
	count = 0;
	if (sym_type == 0)
		return (1);
	else if (sym_type == 1 || sym_type == 3)
		count = 2 + count_space(s + 2);
	else if (sym_type == 2 || sym_type > 3)
		count = 1 + count_space(s + 1);
	while ((!ft_find(s + count, sym) && (s[count] != ' ' && s[count] != '\t')
			&& s[count]) || (((queot % 2) || (double_qu % 2)) && s[count]))
	{
		queot += (*(s + count) == 34) * !(double_qu % 2);
		double_qu += (*(s + count) == 39) * !(queot % 2);
		count++;
	}
	return (count);
}

//ft_printf("`q =%d dq=%d sym = %d find =%d\n",(queot % 2) , (double_qu % 2), (s[count] != ' ' && s[count] != '\t'), ft_find(s + count, sym));

int	get_token_len(char *s, char **sym)
{
	int	queot;
	int	double_qu;
	int	count;

	queot = 0;
	double_qu = 0;
	count = 0;
	while (*(s))
	{
		queot += (*s == 34) * !(double_qu % 2);
		double_qu += (*s == 39) * !(queot % 2);
		if (ft_find(s, sym) && !(queot % 2) && !(double_qu % 2))
			break ;
		count++;
		s++;
	}
	return (count);
}

int	*word_len(char *s, char **sym, int part)
{
	int	*array;
	int	i;

	array = (int *)ft_calloc(part * 2, sizeof(int));
	if (!array)
		return (NULL);
	i = 0;
	while (*s && i < part)
	{
		array[i] = get_token_len(s, sym);
		s += array[i];
		s += count_space(s);
		if (++i < part && ft_find(s, sym))
			array[i] = get_symb_len(ft_find(s, sym) - 1, s, sym);
		if (i < part)
			s += array[i++];
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
	k = 0;
	while (s[k])
	{
		if (len_array[i] != 0)
			array[i][++j] = s[k++];
		if (--len_array[i] < 1)
		{
			array[i][++j] = '\0';
			i++;
			j = -1;
			l += len_array[i] + 1;
		}
	}
	return (array);
}

char	**expr_split(char *s, char **sym, int part)
{
	char	**array;
	int		*len_array;
	int		i;

	array = NULL;
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
	array = word_cutter(s, len_array, array);
	array[part] = NULL;
	free(len_array);
	return (array);
}

//>>> MiniShell $> MiniShell $>"l""s"'|'"gre""p"
//minshell: error unexpected token '>'
//minishell(51477,0x116491dc0) malloc: Incorrect checksum for freed object 0x7fc38ac19de0: probably modified after being freed.
//Corrupt value: 0x0
//minishell(51477,0x116491dc0) malloc: *** set a breakpoint in malloc_error_break to debug
//[1]    51477 abort      ./minishell*/