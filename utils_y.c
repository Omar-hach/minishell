/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_y.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:47:04 by yhachami          #+#    #+#             */
/*   Updated: 2023/04/28 15:47:07 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*check_path(char *dir, char *file)
{
	char	*path;
	int		y;
	int		z;

	y = -1;
	z = -1;
	path = (char *)malloc(ft_strlen(dir) + ft_strlen(file) + 2);
	if (!path)
		return (NULL);
	while (dir[++y])
		path[y] = dir[y];
	path[y++] = '/';
	while (file[++z])
		path[y + z] = file[z];
	path[y + z] = '\0';
	if (access(path, F_OK) == 0)
		return (path);
	free(path);
	path = NULL;
	return (NULL);
}

char	*get_path(char *dir, char *file)
{
	char	*path;
	char	**all_paths;
	int		x;

	all_paths = ft_split(dir, ':');
	if (!all_paths)
		return (NULL);
	path = NULL;
	x = -1;
	while (all_paths[++x] && !path)
		path = check_path(all_paths[x], file);
	free_aray(all_paths);
	return (path);
}

// find path of executable in $PATH (/bin : /usr/bin)
char	*find_path(char *file)
{
	char	*path;
	char	*dir;

	if (!file[0])
		return (NULL);
	dir = getenv("PATH");
	if (dir)
		path = get_path(dir, file);
	else
	{
		dir = (char *)malloc(PATH_MAX);
		if (!dir)
			return (NULL);
		getcwd(dir, PATH_MAX);
		path = check_path(dir, file);
		free(dir);
	}
	return (path);
}

int	check_file(char *file)
{
	int		len;
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

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_printf("couldnt fork\n");
		return (-1);
	}
	return (pid);
}

	// ft_printf("fd=%d | %d\n",fd,fd2replace);
int	ft_dup(int fd, int fd2replace)
{
	if (dup2(fd, fd2replace) < 0)
	{
		ft_printf("%d, couldnt redirect to fd %d\n", fd, fd2replace);
		return (-1);
	}
	return (0);
}
