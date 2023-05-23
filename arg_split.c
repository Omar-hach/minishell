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

	// ft_printf("%d" , (qt % 2));
	// ft_printf("%d" , (dualqt % 2));

	// skip = (s[y] == '\'') * !(dualqt % 2);
	// qt += (s[y] == '\'') * !(dualqt % 2);

	// skip = (s[y] == '\"') * !(qt % 2);
	// dualqt += (s[y] == '\"') * !(qt % 2);

	// if ((s[y] != '\"' && s[y] != '\'') || ((s[y] == '\"' || s[y] == '\'')
	// 	&& (!(qt % 2) || !(dualqt % 2)) && skip == 0))
	// {
	// 	s[z] = s[y];
	// 	z++;
	// }

int	skip_quote(char *s, int y, int z)
{
	int		skip;
	int		qt;
	int		dualqt;
	int		QQQ;

	qt = 0;
	dualqt = 0;
	QQQ = 0;
	while (s[y])
	{
		skip = 0;
		if ((s[y] == '\'') && !(dualqt % 2))
		{	
			qt++;
			skip = 1;
			QQQ = 1;
		}
		if ((s[y] == '\"') && !(qt % 2))
		{
			dualqt++;
			skip = 1;
			QQQ = 1;
		}
		if ((s[y] != '\"' && s[y] != '\'')
			|| ((s[y] == '\"') && !(dualqt % 2) && skip == 0)
			|| ((s[y] == '\'') && !(qt % 2) && skip == 0))
		{
			s[z] = s[y];
			z++;
		}
		y++;
	}
	s[z] = '\0';
	return (QQQ);
}

void	ft_skip(t_token *token, int i)
{
	int		x;
	int		y;
	int		z;

	x = 0;
	while (token[i].args[x])
	{
		// ft_printf("so SQiping %d = ", x); 
		z = 0;
		y = 0;
		token[i].qt = 0;
		token[i].qt = skip_quote(token[i].args[x], 0, 0);
		// ft_printf("\n");
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
	int		qt;
	int		dualqt;

	qt = 0;
	dualqt = 0;
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
		qt += (s[x] == '\"') * !(dualqt % 2);
		dualqt += (s[x] == '\'') * !(qt % 2);
		if (y == -1 && !ft_strchr(c, s[x]))
			y = x;
		else if (y >= 0 && (ft_strchr(c, s[x]) || x == ft_strlen(s))
			&& !(qt % 2) && !(dualqt % 2))
			tbl[z++] = split_word(s, &y, x);
		x++;
	}
	tbl[z] = 0;
	return (tbl);
}
