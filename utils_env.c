/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 00:44:24 by yhachami          #+#    #+#             */
/*   Updated: 2023/06/14 00:44:29 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	change_pwd(char **env)
{
	char	*dir;
	char	*pwd;

	dir = (char *)malloc(PATH_MAX);
	if (!dir)
		return (1);
	getcwd(dir, PATH_MAX);
	pwd = make_var("PWD", dir);
	ft_setenv(env, pwd);
	free(dir);
	return (0);
}

int	change_oldpwd(char **env)
{
	char	*dir;
	char	*oldpwd;

	dir = (char *)malloc(PATH_MAX);
	if (!dir)
		return (1);
	getcwd(dir, PATH_MAX);
	oldpwd = make_var("OLDPWD", dir);
	ft_setenv(env, oldpwd);
	free(dir);
	return (0);
}

int	ft_env_declare(char **env)
{
	int			x;
	int			y;
	int			z;

	x = -1;
	while (env[++x])
	{
		printf("declare -x ");
		y = -1;
		z = 0;
		while (env[x][++y])
		{
			printf("%c", env[x][y]);
			if (env[x][y] == '=')
			{
				printf("\"");
				z = 1;
			}
		}
		if (z)
			printf("\"");
		printf("\n");
	}
	return (0);
}
