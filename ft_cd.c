/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:22:32 by yhachami          #+#    #+#             */
/*   Updated: 2023/05/13 20:22:35 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_pwd()
{
	char	*dir;

	dir = (char *)malloc(PATH_MAX);
	if (!dir)
		return (1);
	getcwd(dir, PATH_MAX);
	printf("%s\n", dir);
	free(dir);
	return (0);
}

char	*extra_cd(char *path)
{
	if (path[0] == '-' && !path[1])
	{
		path = getenv("OLDPWD");
		if (!path)
		{
			ft_printf("cd: OLDPWD not set\n");
			return (0);
		}
		else
			printf("%s\n", path);
	}
	return (path);
}

int	change_dir(char *path)
{
	DIR	*dir;

	dir = opendir(path);
	if (dir)
	{
		closedir(dir);
		if (chdir(path) < 0)
		{
			ft_printf("cd: couldnt change working directory\n");
			return (1);
		}
	}
	else
	{
		ft_printf("cd: %s: No such file or directory\n", path);
		return (1);
	}
	return (0);
}

int	ft_cd(int ac, char **av)
{
	char	*path;
	int		out;

	if (ac == 0)
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_printf("cd: HOME not set\n");
			return (3);
		}
	}
	else
	{
		path = extra_cd(av[0]);
		if (!path)
			return (1);
	}
	out = change_dir(path);
	// ft_printf(" cd %s \n", path);
	// if (path)
	// 	free(path);
	return (out);
}
