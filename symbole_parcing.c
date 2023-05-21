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
	if (sym_type < 2)
		return (1);
	else if (sym_type == 2 || sym_type == 4)
		count = 2 + count_space(s + 2);
	else if (sym_type == 3 || sym_type == 5)
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

int put_inderect(char *s, int end, char *re)
{
	int k;
	int j;

	k = -1;
	j = ft_strlen(re);
	while(++k < end + 1)
	{
		if(count_space(s + k) == ft_strlen(s))
			return (0);

		k += count_space(s + k);
		re[j++] = s[k];
		s[k] = ' ';
	}
	return (j);
}

char	*rearrange_input(char *s, char **sym, int i)
{
	char	*re;
	int		j;

	re = (char *)ft_calloc(ft_strlen(s) + 5,sizeof(char));
	if (!re)
		return (NULL);
	j = 0;
	while (s[++i])
	{
		// if (count_space(s + i) > 1)
		// 	i += count_space(s + i);
		if(ft_find(s + i, sym) > 1 && is_outside_quoet(s, i))
			i += get_symb_len(ft_find(s + i, sym), s + i, sym) - 1;
		else if (ft_find(s + i, sym) == 1 && is_outside_quoet(s, i))
			j = put_inderect(s, i, re);
		else
		{
			re[j++] = s[i];
			s[i] = ' ';
		}
	}
	put_inderect(s, i, re);
	//free(s);
	return (re);
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

int	*words_len(char *s, char **sym, int part,char **arrays)
{
	int	*larray;
	int	i;

	larray = (int *)ft_calloc(part + 1, sizeof(int));
	if (!larray)
	{
		free(arrays);
		return (NULL);
	}
	i = 0;
	while (*s && i < part)
	{
		s += larray[i];
		if (i < part && ft_find(s, sym))
			larray[i] = get_symb_len(ft_find(s, sym), s, sym);
		else
			larray[i] = get_token_len(s, sym);
		if (i < part)
			s += larray[i++];
	}
	return (larray);
}

char	**words_cutter(char *s, int *len_array, char **array, int part)
{
	int		i;
	int		l;
	int		j;
	int		k;

	l = len_array[0];
	i = 0;
	j = -1;
	k = 0;
	while (i < part)// || s[k])
	{
		if (len_array[i] == 0)
			array[i++] = NULL;
		if (l != 0 && len_array[i])
			array[i][++j] = s[k++];
		if (--l < 1 && len_array[i])
		{
			array[i][++j] = '\0';
			i++;
			j = -1;
			l += len_array[i];
		}
	}
	return (array);
}

char	**expr_split(char *input, char **sym, int part)
{
	char	**array;
	char	*s;
	int		*len_array;
	int		i;

	array = NULL;
	s = rearrange_input(input, sym, -1); // printf("s=%s.\n",s);
	if (detect_sym_error(s, sym, &part))
	{
		*error = 2;
		return (NULL);
	}
	array = (char **)ft_calloc(part + 1, sizeof(char *));
	if (!array)
		return (NULL);
	len_array = words_len(s + count_space(s), sym, part, array);
	if (!len_array)
		return (NULL);
	i = -1;
	while (++i < part)
		array[i] = (char *)ft_calloc(len_array[i] + 1, sizeof(char));
	array = words_cutter(s + count_space(s), len_array, array, part);
	array[part] = NULL;
	free(s);
	free(len_array);
	return (array);
}
