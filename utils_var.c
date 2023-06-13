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

int	change_oldpwd(void)
{
	char	*dir;

	dir = (char *)malloc(PATH_MAX);
	if (!dir)
		return (1);
	getcwd(dir, PATH_MAX);
	replace_var("OLDPWD", dir);
	free(dir);
	return (0);
}

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

void	ft_setenv(char *var)
{
	extern char	**environ;
	char		**new_env;
	int			x;

	x = ft_findvar(var);
	if (x >= 0)
	{
		x = 0;
		while (environ[x])
			x++;
		new_env = (char **) ft_calloc((x + 2), sizeof(char *));
		if (new_env)
			return ;
		x = ft_findvar(var);
		new_env[x] = var;
		environ = new_env;	
	}
	else
		ft_putenv(var);
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
		size = ft_strlen(name) + ft_strlen(value) + 1;
		val = (char *) malloc(size * sizeof(char));
		if (!val)
			return (0);
		y = -1;
		while (name[++y])
			val[y] = name[y];
		val[y] = '=';
		x = 0;
		while (value[x])
			val[y] = value[x++];
		val[y] = '\0';
		// x = ft_findvar(name);
		// environ[x] = val;
		ft_setenv(val);
		// free(val);
		return (0);
	}
	else
		return (-1);
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
		new_env = (char **) ft_calloc((x + 2), sizeof(char *));
		if (!new_env)
			return ;
		x = -1;
		while (environ[++x])
			new_env[x] = environ[x];
		var_ = environ[--x];
		new_env[x++] = ft_strdup(var);
		new_env[x++] = var_;
		new_env[x] = NULL;
		environ = new_env;
	}
	// else
	// 	environ[x] = ft_strdup(var);
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
