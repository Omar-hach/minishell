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

	// ft_printf("s=%d n=%d val=%d\n",ft_strlen(s),name_len,ft_strlen(val));
	size = ft_strlen(s) - name_len + ft_strlen(val) + 1;
	no_money = (char *) malloc (size * sizeof(char));
	x = -1;
	while (++x < start)
		no_money[x] = s[x];
	y = -1;
	while (++y < ft_strlen(val))
		no_money[x + y] = val[y];
	y += x;
	x += name_len + 1;
	while (x < size)
		no_money[y++] = s[x++];
	no_money[x] = '\0';
	return (no_money);
}

// remove dolar var
char	*tax_dollars(char *s, int start, int name_len, char *name)
{
	int		x;
	int		y;

	(void)(name);
	// if (!ft_isvar(name))
	// 	return (s);
	x = start;
	y = start + name_len + 1;
	while (s[y])
		s[x++] = s[y++];
	s[x] = '\0';
	return (s);
}

char	*get_dollar_name(char *s, int x, int z)
{
	int		y;
	char	*name;

	name = (char *) malloc ((z + 1) * sizeof(char));
	y = x;
	z = 0;
	while (s[++y] && s[y] != ' ' && s[y] != '$' && s[y] != '\''
		&& s[y] != '\"' && s[y] != '/' && s[y] != '=')
	{
		name[z++] = s[y];
		if (y == x + 1 && (s[y] >= '0' && s[y] <= '9'))
			break;
	}
	name[z] = '\0';
	return (name);
}

// get start and lenght of dolar var
char	*get_dollars(char *s, int *x, int qt)
{
	int		y;
	int		z;
	char	*name;
	char	*val;
	char	*out;

	y = *x;
	z = 0;
	while (s[++y] && s[y] != ' ' && s[y] != '$' && s[y] != '\''
		&& s[y] != '\"' && s[y] != '/' && s[y] != '=')
	{
		z++;
		if (y == *x + 1 && (s[y] >= '0' && s[y] <= '9'))
			break;
	}
	if (z == 0 && (qt == 0 || !s[y]))
		return (s);
	name = get_dollar_name(s, *x, z);
	// ft_printf("name = %s\n",name);
	val = getenv(name);
	if (!val)
		out = tax_dollars(s, *x, z, name);
	else
		out = mint_dollars(s, *x, z, val);
	*x -= 1;
	return (out);
}

// search for all  dolar var
char	*replace_dollars(char *s)
{
	int		x;
	char	*out;
	int		qt;
	int		dualqt;

	qt = 0;
	dualqt = 0;
	x = 0;
	while (s[x] && s[x] != '$')
		x++;
	if (x == ft_strlen(s))
		return (s);
	out = s;
	x = -1;
	while (out[++x])
	{
		dualqt += (out[x] == '\"') * !(qt % 2);
		qt += (out[x] == '\'') * !(dualqt % 2);
		if (out[x] == '$' && !(qt % 2))
			out = get_dollars(out, &x, !(dualqt % 2));
	}
	return (out);
}
