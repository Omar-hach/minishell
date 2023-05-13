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

// replace dolar var
char	*mint_dollars(char *s, int start, int name_len, char *val)
{
	int		size;
	char	*no_money;
	int		x;
	int		y;

	size = ft_strlen(s) - name_len + ft_strlen(val) + 1;
	no_money = (char *) malloc (size * sizeof(char));
	x = -1;
	while (++x <= start)
		no_money[x] = s[x];
	y = 0;
	while (y < ft_strlen(val))
	{
		no_money[x + y] = val[y];
		y++;
	}
	y += x;
	x += name_len + 1;
	while (x < size)
		no_money[y++] = s[x++];
	no_money[x] = '\0';
	return (no_money);
}

char	*tax_dollars(char *s, int start, int name_len)
{
	int		x;
	int		y;

	x = 0;
	while (x <= start)
		x++;
	y = x + name_len + 1;
	while (s[y])
		s[x++] = s[y++];
	s[x] = '\0';
	return (s);
}

// get start and lenght of dolar var

char	*get_dollars(char *s, int x)
{
	int		y;
	int		z;
	char	*name;
	char	*val;
	char	*out;

	y = x;
	z = 0;
	while (s[++x] && s[x] != ' ' && s[x] != '$')
		z++;
	if (z < 1)
		return (s);
	name = (char *) malloc (z * sizeof(char));
	x = y;
	z = 0;
	while (s[++x] && s[x] != ' ' && s[x] != '$')
		name[z++] = s[x];
	name[z] = '\0';
	val = getenv(name);
	if (!val)
		out = tax_dollars(s, y - 1, z);
	else
		out = mint_dollars(s, y - 1, z, val);
	return (out);
}

// search for all  dolar var

char	*replace_dollars(char *s)
{
	int		x;
	char	*out;

	x = 0;
	while (s[x] && s[x] != '$')
		x++;
	if (x == ft_strlen(s))
		return (0);
	out = s;
	x = -1;
	while (out[++x])
	{
		if (out[x] == '$')
			out = get_dollars(out, x);
	}
	return (out);
}
