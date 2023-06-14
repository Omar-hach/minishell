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

char	*get_path(char **all_paths, char *file, int x)
{
	char	*path;
	int		y;
	int		z;

	path = NULL;
	while (all_paths[++x] && !path)
	{
		y = -1;
		z = -1;
		path = (char *)malloc(ft_strlen(all_paths[x]) + ft_strlen(file) + 2);
		if (!path)
			return (NULL);
		while (all_paths[x][++y])
			path[y] = all_paths[x][y];
		path[y++] = '/';
		while (file[++z])
			path[y + z] = file[z];
		path[y + z] = '\0';
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	return (path);
}

// find path of executable in $PATH (/bin : /usr/bin)
char	*find_path(char *file)
{
	char	*path;
	char	**all_paths;

	// printf("file=%s,\n",file);
	if (!file[0])
		return (NULL);
	all_paths = ft_split(getenv("PATH"), ':');
	if (!all_paths)
		return (NULL);
	path = get_path(all_paths, file, -1);
	free_aray(all_paths);
	// printf("path=%s\n",path);
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
