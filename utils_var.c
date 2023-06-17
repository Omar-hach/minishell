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

//look for variable in environment
int	ft_findvar(char **env, char *var)
{
	int			size;
	int			x;

	x = 0;
	while (env[x])
	{
		size = 0;
		while (var[size] && var[size] != '=')
			size++;
		if (env[x][size] == '=' && ft_strncmp(env[x], var, size) == 0)
			return (x);
		x++;
	}
	return (-1);
}

// make string of variable "name=value"
char	*make_var(char *name, char *value)
{
	int		x;
	int		y;
	int		size;
	char	*val;

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

//add or replace variable in environment
void	ft_setenv(char **env, char *var)
{
	int			x;
	char		*old;

	x = ft_findvar(env, var);
	if (x >= 0)
	{
		old = env[x];
		env[x] = var;
		free(old);
	}
	else
	{
		x = 0;
		while (env[x])
			x++;
		env[x++] = var;
		env[x] = NULL;
	}
}

//remove from variable from environment
void	ft_unsetenv(char **env, char *name)
{
	int			x;
	int			lul;

	lul = ft_findvar(env, name);
	x = lul;
	if (lul > -1)
	{
		free(env[lul]);
		while (lul == x || env[x])
		{
			if (env[x + 1])
				env[x] = env[x + 1];
			x++;
		}
		env[--x] = NULL;
	}
}
