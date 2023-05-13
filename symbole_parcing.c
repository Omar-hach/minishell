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
