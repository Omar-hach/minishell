/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:47:04 by yhachami          #+#    #+#             */
/*   Updated: 2023/04/28 15:47:07 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*join_args(char **args, char between)
{
	int		x;
	int		i;
	int		j;
	int		size;
	char	*out;

	size = 0;
	i = -1;
	while (args[++i])
		size += ft_strlen(args[i]) + 1;
	out = (char *) malloc(size * sizeof(char));
	x = -1;
	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
			out[++x] = args[i][j];
		out[++x] = between;
	}
	out[x] = '\0';
	return (out);
}

char	*ft_strdup_newline(char *s)
{
	int		i;
	int		size;
	char	*out;

	size = ft_strlen(s) + 1;
	out = (char *) malloc(size * sizeof(char));
	i = -1;
	while (s[++i])
		out[i] = s[i];
	out[i] = '\n';
	out[i + 1] = '\0';
	return (out);
}

// find path of executable in $PATH (/bin : /usr/bin)
char	*find_path(char *file)
{
	int		x;
	int		y;
	int		z;
	char	*path;
	char	**all_paths;

	all_paths = ft_split(getenv("PATH"), ':');
	x = -1;
	while (all_paths[++x])
	{
		y = -1;
		z = -1;
		path = (char *) malloc(ft_strlen (all_paths[x]) + ft_strlen (file) + 2);
		while (all_paths[x][++y])
			path[y] = all_paths[x][y];
		path[y++] = '/';
		while (file[++z])
			path[y + z] = file[z];
		path[y + z] = '\0';
		if (access(path, F_OK) == 0)
			return (path);
	}
	return (0);
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
