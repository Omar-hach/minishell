/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollars.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:54:47 by yhachami          #+#    #+#             */
/*   Updated: 2023/05/08 21:54:50 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// make the dola
// ft_printf("s=%d n=%d val=%d\n",ft_strlen(s),name_len,ft_strlen(val));
char	*mint_dollars(char *s, int start, int name_len, char *val)
{
	int		size;
	char	*no_money;
	int		x;
	int		y;

	size = ft_strlen(s) - name_len + ft_strlen(val) + 1;
	no_money = (char *) malloc ((size + 1) * sizeof(char));
	if (!no_money)
		return (s);
	x = -1;
	while (++x < start)
		no_money[x] = s[x];
	y = -1;
	while (++y < ft_strlen(val))
		no_money[x + y] = val[y];
	y += x;
	x += name_len + 1;
	while (s[x])
		no_money[y++] = s[x++];
	no_money[y] = '\0';
	free(s);
	return (no_money);
}

// remove the dolar
char	*tax_dollars(char *s, int start, int name_len)
{
	char	*no_money;
	int		size;
	int		x;
	int		y;

	size = ft_strlen(s) - name_len + 1;
	no_money = (char *) malloc ((size + 1) * sizeof(char));
	if (!no_money)
		return (s);
	y = -1;
	while (++y <= start && s[y])
		no_money[y] = s[y];
	x = start;
	y = start + name_len + 1;
	while (s[y])
		no_money[x++] = s[y++];
	no_money[x] = '\0';
	free(s);
	return (no_money);
}

// get the size of the dola
char	*get_dollars(char *s, int *x, int qt)
{
	int		y;
	int		z;
	char	*name;
	char	*val;
	char	*out;

	y = *x;
	z = 0;
	while (s[++y] && is_money_end(s[y]))
	{
		z++;
		if (y == (*x) + 1 && ft_isdigit(s[y]))
			break ;
	}
	if (z == 0 && (qt == 0 || !s[y]))
		return (s);
	name = get_dollar_name(s, *x, z);
	val = getenv(name);
	if (!val)
		out = tax_dollars(s, *x, z);
	else
		out = mint_dollars(s, *x, z, val);
	*x -= 1;
	free(name);
	return (out);
}

//look for the dola
char	*is_money(char *s, int *x, int qt, int dualqt)
{
	char	*home;
	char	*hmm;

	if (s[*x] == '$' && s[(*x) + 1] == '?' && !(qt % 2))
	{
		hmm = ft_itoa(*g_error);
		s = mint_dollars(s, *x, 1, hmm);
		free(hmm);
	}
	else if (s[*x] == '$' && !(qt % 2))
		s = get_dollars(s, x, !(dualqt % 2));
	else if (s[*x] == '~' && !(qt % 2) && !(dualqt % 2)
		&& ft_isdigit(s[(*x) + 1]) == 0 && ft_isdigit(s[(*x) - 1]) == 0)
	{
		home = getenv("HOME");
		if (home)
			s = mint_dollars(s, *x, 0, home);
		else
			ft_printf("~: HOME not set\n");
	}
	return (s);
}

// search for all the dolas
char	*replace_dollars(char *word)
{
	int		x;
	int		qt;
	int		dualqt;
	char	*s;

	qt = 0;
	dualqt = 0;
	x = 0;
	s = ft_strdup(word);
	while (s[x] && s[x] != '$' && s[x] != '~')
		x++;
	if (x == ft_strlen(s))
		return (s);
	x = -1;
	while (s[++x])
	{
		dualqt += (s[x] == '\"') * !(qt % 2);
		qt += (s[x] == '\'') * !(dualqt % 2);
		s = is_money(s, &x, qt, dualqt);
	}
	return (s);
}
// ft_printf("[%d] s = %s\n",x ,s);
