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

// check if quote is inside another quote
int	is_quote_skip(char c, int *qt, int *dualqt, int *qted)
{
	int		skip;

	skip = 0;
	if ((c == '\'') && !(*dualqt % 2))
	{
		*qt += 1;
		skip = 1;
		*qted = 1;
	}
	if ((c == '\"') && !(*qt % 2))
	{
		*dualqt += 1;
		skip = 1;
		*qted = 1;
	}
	return (skip);
}

// check if variable has valide name 2
int	is_varname(char *var)
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

// check if variable has valide name
int	is_var(char *var)
{
	int	x;
	int	val;

	val = is_varname(var);
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

//check if executable file is valid file and is not a directory
int	check_file(char *file)
{
	DIR		*dir;

	dir = opendir(file);
	if (dir)
	{
		closedir(dir);
		ft_printf(" %s: is a directory\n", file);
		return (126);
	}
	if (access(file, X_OK) != 0)
	{
		ft_printf(" %s: No such file or directory\n", file);
		return (127);
	}
	return (0);
}

//check if $VAR has ended
int	is_money_end(char c)
{
	if (c != ' ' && c != '$' && c != '\''
		&& c != '\"' && c != '/' && c != '=' && c != '?')
		return (1);
	else
		return (0);
}
