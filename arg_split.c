/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 17:51:04 by yhachami          #+#    #+#             */
/*   Updated: 2023/05/18 17:51:08 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quote(char *s, int x, int y)
{
	int		skip;
	int		qt;
	int		dualqt;
	int		qted;

	qt = 0;
	dualqt = 0;
	qted = 0;
	while (s[x])
	{
		skip = is_quote_skip(s[x], &qt, &dualqt, &qted);
		if ((s[x] != '\"' && s[x] != '\'')
			|| ((s[x] == '\"') && !(dualqt % 2) && skip == 0)
			|| ((s[x] == '\'') && !(qt % 2) && skip == 0))
		{
			s[y] = s[x];
			y++;
		}
		x++;
	}
	s[y] = '\0';
	return (qted);
}

void	ft_skip(t_token *token, int i)
{
	int		x;
	int		y;
	int		z;

	x = 0;
	while (token[i].args[x])
	{
		z = 0;
		y = 0;
		token[i].qt = 0;
		token[i].qt = skip_quote(token[i].args[x], 0, 0);
		x++;
	}
}

static int	count_words(char const *s, char *c)
{
	int	count;
	int	i;
	int	word;

	i = 0;
	count = 0;
	word = 0;
	while (i <= ft_strlen(s))
	{
		if (!ft_strchr(c, s[i]) && word == 0)
			word = 1;
		else if ((ft_strchr(c, s[i]) || !s[i]) && word == 1)
		{
			word = 0;
			count++;
		}
		i++;
	}
	return (count +1);
}

static char	*split_word(char const *s, int *start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - *start + 1));
	if (!word)
		return (0);
	while (i < (end - *start) && s[i])
	{
		word[i] = s[*start + i];
		i++;
	}
	*start = -1;
	word[i] = '\0';
	return (word);
}

char	**arg_split(char *s, char *c)
{
	char	**tbl;
	int		x;
	int		y;
	int		z;

	if (!s)
		return (0);
	tbl = malloc(count_words(s, c) * sizeof(char *));
	if (!tbl)
		return (0);
	x = 0;
	y = -1;
	z = 0;
	while (x <= ft_strlen(s))
	{
		if (y == -1 && !ft_strchr(c, s[x]))
			y = x;
		else if (y >= 0 && (ft_strchr(c, s[x]) || x == ft_strlen(s))
			&& is_outside_quoet(s, x))
			tbl[z++] = split_word(s, &y, x);
		x++;
	}
	tbl[z] = 0;
	return (tbl);
}
