/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:40:59 by yhachami          #+#    #+#             */
/*   Updated: 2023/04/28 15:41:06 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_piped_end(int *fd, int io, t_tree *tree, t_token *tokens)
{
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
	return (exec_node(tree, tokens));
}

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
		out = ft_piped_end(fd, 0, tree->right_son, tokens);
	pid[2] = fork1();
	if (pid[2] == 0)
		out = ft_piped_end(fd, 1, tree->left_son, tokens);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid[1], NULL, 0);
	waitpid(pid[2], NULL, 0);
	free(fd);
	free(pid);
	return (out);
}

int	ft_redirect_in(t_tree *tree, t_token *tokens)
{
	int	fd;
	int	x;

	// ft_printf("<\n");
	if (fork1() == 0)
	{
		x = tree->token_index;
		fd = open(tokens[x].arg, O_RDWR | O_CREAT, 0644);
		if (fd < 0)
		{
			perror("couldnt open file");
			return (1);
		}
		if (ft_dup(fd, STDIN_FILENO) < 0)
			return (2);
		exec_node(tree->left_son, tokens);
		close(fd);
	}
	wait(NULL);
	return (0);
}

int	ft_redirect_in_append(t_tree *tree, t_token *tokens)
{
	int	fd;
	int	x;

	// ft_printf("<<\n");
	if (fork1() == 0)
	{
		x = tree->token_index;
		fd = open(tokens[x].arg, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("couldnt open file");
			return (1);
		}
		if (ft_dup(fd, STDIN_FILENO) < 0)
			return (2);
		exec_node(tree->left_son, tokens);
		close(fd);
	}
	wait(NULL);
	return (0);
}

int	ft_redirect_out(t_tree *tree, t_token *tokens)
{
	int	fd;
	int	x;

	// ft_printf(">\n");
	if (fork1() == 0)
	{
		x = tree->token_index;
		fd = open(tokens[x].arg, O_RDWR | O_CREAT, 0644);
		if (fd < 0)
		{	
			perror("couldnt open file");
			return (1);
		}
		if (ft_dup(fd, STDOUT_FILENO) < 0)
			return (2);
		exec_node(tree->left_son, tokens);
		close(fd);
	}
	else if (tokens[tree->father->token_index].type == 20)
		exec_node(tree->left_son, tokens);
	wait(NULL);
	return (0);
}

int	ft_redirect_out_append(t_tree *tree, t_token *tokens)
{
	int	fd;
	int	x;

	// ft_printf(">>\n");
	if (fork1() == 0)
	{
		x = tree->token_index;
		fd = open(tokens[x].arg, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd < 0)
		{
			perror("couldnt open file");
			return (1);
		}
		if (ft_dup(fd, STDOUT_FILENO) < 0)
			return (2);
		exec_node(tree->left_son, tokens);
		close(fd);
	}
	else if (tokens[tree->father->token_index].type == 20)
		exec_node(tree->left_son, tokens);
	wait(NULL);
	return (0);
}

int	exec_symbol(t_tree *tree, t_token *tokens)
{
	int	x;
	int	out;

	x = tree->token_index;
	// ft_printf("x = %d\n", x);
	if (tokens[x].type == 20)
		out = ft_pipe(tree, tokens);
	else if (tokens[x].type == 21)
		out = ft_redirect_in(tree, tokens);
	else if (tokens[x].type == 22)
		out = ft_redirect_in_append(tree, tokens);
	else if (tokens[x].type == 23)
		out = ft_redirect_out(tree, tokens);
	else if (tokens[x].type == 24)
		out = ft_redirect_out_append(tree, tokens);
	return (out);
}
