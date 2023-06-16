/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:38:41 by yhachami          #+#    #+#             */
/*   Updated: 2023/05/01 19:38:46 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

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

char	*make_var(char *name, char *value)
{
	int			x;
	int			y;
	int			size;
	char		*val;

	size = ft_strlen(name) + ft_strlen(value) + 2;
	val = (char *) malloc(size * sizeof(char));
	if (!val)
		return (0);
	y = -1;
	while (name[++y])
		val[y] = name[y];
	val[y] = '=';
	x = -1;
	while (value[++x])
		val[++y] = value[x];
	val[++y] = '\0';
	return (val);
}

void	ft_putenv(char *var)
{
	extern char	**environ;
	char		**new_env;
	int			x;

	x = 0;
	while (environ[x])
		x++;
	new_env = (char **) ft_calloc((x + 2), sizeof(char *));
	if (!new_env)
		return ;
	x = -1;
	while (environ[++x])
		new_env[x] = ft_strdup(environ[x]);
	new_env[x++] = var;
	new_env[x] = NULL;
	free_env();
	environ = new_env;
}

void	ft_setenv(char *var)
{
	extern char	**environ;
	int			x;
	char		*old;

	x = ft_findvar(var);
	if (x >= 0)
	{
		old = environ[x];
		environ[x] = var;
		free(old);
	}
	else
		ft_putenv(var);
}

void	ft_unsetenv(char *name)
{
	extern char	**environ;
	int			x;
	int			lul;

	lul = ft_findvar(name);
	x = lul;
	if (lul > -1)
	{
		free(environ[lul]);
		while (lul == x || environ[x])
		{
			if (environ[x + 1])
				environ[x] = environ[x + 1];
			x++;
		}
		environ[--x] = NULL;
	}
}
