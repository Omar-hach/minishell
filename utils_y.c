/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_y.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:47:04 by yhachami          #+#    #+#             */
/*   Updated: 2023/04/28 15:47:07 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// find path of executable in $PATH (/bin : /usr/bin)
char	*find_path(char *file, int x, int y, int z)
{
	char	*path;
	char	**all_paths;

	all_paths = ft_split(getenv("PATH"), ':');
	path = NULL;
	while (all_paths[++x] && !path)
	{
		y = -1;
		z = -1;
		path = (char *)ft_calloc(ft_strlen(all_paths[x])
				+ ft_strlen(file) + 2, 1);
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
	// free_aray(all_paths);
	return (path);
}

int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("couldnt fork");
		return (-1);
	}
	return (pid);
}

	// ft_printf("fd=%d | %d\n",fd,fd2replace);
int	ft_dup(int fd, int fd2replace)
{
	if (dup2(fd, fd2replace) < 0)
	{
		perror("couldnt redirect to fd ");
		return (-1);
	}
	return (0);
}
