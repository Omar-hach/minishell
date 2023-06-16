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

int	change_pwd(void)
{
	char	*dir;
	char	*pwd;

	dir = (char *)malloc(PATH_MAX);
	if (!dir)
		return (1);
	getcwd(dir, PATH_MAX);
	pwd = make_var("PWD", dir);
	ft_setenv(pwd);
	free(dir);
	return (0);
}

int	change_oldpwd(void)
{
	char	*dir;
	char	*oldpwd;

	dir = (char *)malloc(PATH_MAX);
	if (!dir)
		return (1);
	getcwd(dir, PATH_MAX);
	oldpwd = make_var("OLDPWD", dir);
	ft_setenv(oldpwd);
	free(dir);
	return (0);
}

int	ft_env_declare(void)
{
	int			x;
	int			y;
	int			z;
	extern char	**environ;

	x = -1;
	while (environ[++x])
	{
		printf("declare -x ");
		y = -1;
		z = 0;
		while (environ[x][++y])
		{
			printf("%c", environ[x][y]);
			if (environ[x][y] == '=')
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
