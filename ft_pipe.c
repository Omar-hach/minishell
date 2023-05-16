/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 23:41:05 by yhachami          #+#    #+#             */
/*   Updated: 2023/05/16 23:41:10 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_piped_end(int *fd, int io, t_tree *tree, t_token *tokens)
{
	int	out;

	if (io == 0)
	{
		if (ft_dup(fd[0], STDIN_FILENO) < 0)
			return (2);
	}
	else
	{
		if (ft_dup(fd[1], STDOUT_FILENO) < 0)
			return (2);
	}
	close(fd[0]);
	close(fd[1]);
	out = exec_node(tree, tokens);
	exit(out);
}

//     pipe
// 1  - - - >  0

int	ft_pipe(t_tree *tree, t_token *tokens)
{
	int		*pid;
	int		*fd;
	int		out;

	out = 0;
	pid = (int *) malloc(2 * sizeof(int));
	fd = (int *) malloc(2 * sizeof(int));
	if (pipe(fd) < 0)
		return (1);
	pid[1] = fork1();
	if (pid[1] == 0)
		ft_piped_end(fd, 0, tree->left_son, tokens);
	pid[2] = fork1();
	if (pid[2] == 0)
		ft_piped_end(fd, 1, tree->right_son, tokens);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[1], &out, 0);
	waitpid(pid[2], &out, 0);
	free(fd);
	free(pid);
	return (out);
}
