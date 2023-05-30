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

// find path of executable in $PATH (/bin : /usr/bin)
char	*find_path(char *file, int x, int y, int z)
{
	char	*path;
	char	**all_paths;

	all_paths = ft_split(getenv("PATH"), ':');
	if (!all_paths)
		return (NULL);
	path = NULL;
	//ft_printf("ok \n");
	while (all_paths[++x] && !path)
	{
		y = -1;
		z = -1;
		path = (char *)malloc(ft_strlen(all_paths[x]) + ft_strlen(file) + 2);
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
	free_aray(all_paths);
	return (path);
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

int	here_doc(char *s, int qt)
{
	int		*bibe;
	char	*input;

	bibe = (int *) malloc(2 * sizeof(int));
	if (pipe(bibe) < -1)
		return (0);
	while (1)
	{
		// printf("read<<\n");
		input = readline("> ");
		if (!input || !s || ft_strncmp(input, s, ft_strlen(input)) == 0)
			break ;
		if (*(input + count_space(input)))
		{
			if (qt == 0)
				input = replace_dollars(input);
	        write(bibe[1], input, ft_strlen(input));
	        write(bibe[1], "\n", 1);
		}
		free(input);
	}
	close(bibe[1]);
	// printf("<< end\n");
	return (bibe[0]);
}

// int	here_doc(char *s, int qt)
// {
// 	int		*bibe;
// 	char	*input;

// 	bibe = (int *) malloc(2 * sizeof(int));
// 	if (pipe(bibe) < -1)
// 		return (0);
// 	while (1)
// 	{
// 		input = readline("> ");
// 		if (!input || !s || ft_strncmp(input, s, ft_strlen(input)) == 0)
// 			break ;
// 		if (*(input + count_space(input)))
// 		{
// 			if (qt == 0)
// 				input = replace_dollars(input);
// 	        write(bibe[1], input, ft_strlen(input));
// 	        write(bibe[1], "\n", 1);
// 		}
// 		free(input);
// 	}
// 	close(bibe[1]);
// 	return (bibe[0]);
// }

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
