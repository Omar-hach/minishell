/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbole_parcing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 07:46:34 by ohachami          #+#    #+#             */
/*   Updated: 2023/06/13 21:27:25 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	put_inderect(char *s, int end, char *re)
{
	int	k;
	int	j;

	k = -1;
	j = ft_strlen(re);
	while (++k < end + 1)
	{
		if (count_space(s + k) == ft_strlen(s))
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

	re = (char *)ft_calloc(ft_strlen(s) + 5, sizeof(char));
	if (!re)
		return (NULL);
	j = 0;
	while (s[++i])
	{
		if (ft_find(s + i, sym) > 1 && is_outside_quotes(re, j))
			i += get_symb_len(ft_find(s + i, sym), s + i, sym) - 1;
		else if (ft_find(s + i, sym) == 1 && is_outside_quotes(re, j))
			j = put_inderect(s, i, re);
		else
		{
			re[j++] = s[i];
			s[i] = ' ';
		}
	}
	put_inderect(s, i, re);
	ft_memcpy(s, re, ft_strlen(s));
	free(re);
	return (s);
}

int	*words_len(char *s, char **sym, int part, char **wordss)
{
	int	*lwords;
	int	i;

	lwords = (int *)ft_calloc(part + 1, sizeof(int));
	if (!lwords)
	{
		(void)(wordss);
		return (NULL);
	}
	i = 0;
	while (*s && i < part)
	{
		s += lwords[i];
		if (i < part && ft_find(s, sym))
			lwords[i] = get_symb_len(ft_find(s, sym), s, sym);
		else
			lwords[i] = get_token_len(s, sym);
		if (i < part)
			s += lwords[i++];
	}
	return (lwords);
}

char	**words_cutter(char *s, int *len_words, char **words, int part)
{
	int		i;
	int		l;
	int		j;
	int		k;

	l = len_words[0];
	i = 0;
	j = -1;
	k = 0;
	while (i < part)
	{
		if (len_words[i] == 0)
			words[i++] = NULL;
		if (l != 0 && len_words[i])
			words[i][++j] = s[k++];
		if (--l < 1 && len_words[i])
		{
			words[i][++j] = '\0';
			j = -1;
			l += len_words[++i];
		}
	}
	return (words);
}

char	**expr_split(char *input, char **sym)
{
	char	**words;
	int		*len_words;
	char	*s;
	int		i;
	int		part;

	s = rearrange_input(input, sym, -1);
	part = 1;
	if (detect_sym_error(s, sym, &part, 0))
	{
		*g_error = 2;
		return (NULL);
	}
	words = (char **)ft_calloc(part + 2, sizeof(char *));
	if (!words)
		return (NULL);
	len_words = words_len(s + count_space(s), sym, part, words);
	if (!len_words)
		return (NULL);
	i = -1;
	while (++i < part && len_words[i] != 0)
		words[i] = (char *)ft_calloc(len_words[i] + 1, sizeof(char));
	words = words_cutter(s + count_space(s), len_words, words, part);
	free(len_words);
	return (words);
}
