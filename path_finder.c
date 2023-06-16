/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_finder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:58:35 by yhachami          #+#    #+#             */
/*   Updated: 2023/06/15 18:58:38 by yhachami         ###   ########.fr       */
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
	if ((file[0] == '.' && !file[1])
		|| (file[0] == '.' && file[1] == '.' && !file[2]))
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
