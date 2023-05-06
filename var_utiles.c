/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:38:41 by yhachami          #+#    #+#             */
/*   Updated: 2023/05/01 19:38:46 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// int	ft_findvar2(char *var)
// {
// 	int			x;
// 	int 		size;
// 	extern char	**environ;

// 	x = 0;
// 	while (environ[x])
// 	{
// 		size = 0;
// 		while (environ[x][size] != '=')
// 			size++;
// 		if (size == ft_strlen(var) && ft_strncmp(environ[x], var, size) == 0)
// 			return (x);
// 		x++;
// 	}
// 	return (-1);
// }

// void	ft_setenv(char *name)
// {
// 	int			x;
// 	extern char	**environ;

// 	x = ft_findvar(environ, name);
// 	if (x == -1)
// 		ft_putenv(name);
// 	else
// 		environ[x] = ft_strdup(name);
// }

int	ft_findvar(char *var)
{
	int			x;
	int			size;
	extern char	**environ;

	x = 0;
	while (environ[x])
	{
		size = 0;
		while (var[size] && var[size] != '=')
			size++;
		if (environ[x][size] == '=' && ft_strncmp(environ[x], var, size) == 0)
			return (x);
		x++;
	}
	return (-1);
}

int	replace_var(char *name, char *value)
{
	extern char	**environ;
	int			x;
	int			y;
	int			size;
	char		*val;

	x = ft_findvar(name);
	if (x >= 0)
	{
		size = ft_strlen(name) + ft_strlen(value) + 2;
		val = (char *) malloc(size * sizeof(char));
		y = -1;
		while (++y < ft_strlen(name))
			val[y] = name[y];
		val[y] = '=';
		x = 0;
		while (++y < size)
			val[y] = value[x++];
		val[y] = '\0';
		x = ft_findvar(name);
		environ[x] = val;
		return (0);
	}
	else
		return (-1);
}

int	ft_isvar(char *var)
{
	int	size;
	int	x;
	int	y;

	x = -1;
	while (var[++x])
	{
		if (var[x] == '=')
		{
			y = x - 1;
			while (var[y] && (ft_isalnum(var[y]) == 1 || var[y] == '_'))
			{
				y--;
				if (y == -1)
					return (1);
			}
		}
	}
	return (0);
}

void	ft_putenv(char *var)
{
	extern char	**environ;
	char		**new_env;
	char		*var_;
	int			x;

	x = ft_findvar(var);
	if (x == -1)
	{
		x = 0;
		while (environ[x])
			x++;
		new_env = (char **) malloc((x + 2) * sizeof(char *));
		x = -1;
		while (environ[++x])
			new_env[x] = ft_strdup(environ[x]);
		var_ = ft_strdup(environ[--x]);
		new_env[x++] = ft_strdup(var);
		new_env[x++] = var_;
		new_env[x] = NULL;
		environ = new_env;
		free(environ);
	}
	else
		environ[x] = ft_strdup(var);
}

void	ft_unputenv(char *name)
{
	int			x;
	extern char	**environ;

	x = ft_findvar(name);
	if (x > -1)
	{
		while (environ[x])
		{
			if (environ[x + 1])
				environ[x] = environ[x + 1];
			x++;
		}
		environ[--x] = NULL;
	}
}
