/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 03:17:10 by yhachami          #+#    #+#             */
/*   Updated: 2023/05/22 03:17:13 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	check_file(char *file)
{
	int	len;
	DIR		*dir;

	len = ft_strlen(file) - 1;
	if (file[len] == '.')
	{
		ft_printf(" .: filename argument required\n");
		return (2);
	}
	else
	{
		dir = opendir(file);
		if (dir)
		{
			closedir(dir);
			ft_printf(" %s: is a directory\n", file);
			return (126);
		}
	}
	if (access(file, X_OK) != 0)
	{
		ft_printf(" %s: No such file or directory\n", file);
		return (127);
	}
	return (0);
}

int	ft_isvarname(char *var)
{
	int	x;

	if (var[0] == '-')
		return (-3);
	if (ft_isdigit(var[0]) == 1)
		return (-2);
	x = -1;
	while (var[++x] && (var[x] != '='))
	{
		if (ft_isalnum(var[x]) == 0 && var[x] != '_' && var[x] != '\"'
			&& var[x] != '\'' && !(var[x] == '+' && var[x + 1] == '='))
			return (-1);
		if (var[x] == '\\')
			return (-4);
		if (var[x] == ';')
			return (-5);
	}
	return (0);
}

int	ft_isvar(char *var)
{
	int	x;
	int	val;

	val = ft_isvarname(var);
	if (val != 0)
		return (val);
	x = 0;
	while (var[x] && var[x] != '=')
		x++;
	if (var[x] == '=')
		val = 1;
	x--;
	if (var[x] == '+')
		return (2);
	while (var[x] && (ft_isalnum(var[x]) == 1 || var[x] == '_') && val == 1)
	{
		x--;
		if (x == -1)
			return (1);
	}
	if (val == 0)
		return (3);
	return (0);
}

int	money_end(char c)
{
	if (c != ' ' && c != '$' && c != '\''
		&& c != '\"' && c != '/' && c != '=' && c != '?')
		return (1);
	else
		return (0);
}

char	*is_money(char *s, int *x, int qt, int dualqt)
{
	char	*home;

	if (s[*x] == '$' && s[(*x) + 1] == '?' && !(qt % 2))
		s = mint_dollars(s, *x, 1, ft_itoa(*error));
	if (s[*x] == '$' && !(qt % 2))
		s = get_dollars(s, x, !(dualqt % 2));
	if (s[*x] == '~' && !(qt % 2) && !(dualqt % 2)
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
