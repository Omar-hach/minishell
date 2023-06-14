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

	// pid[2] = fork1();
	// if (pid[2] == 0)
	// 	ft_piped_end(bibe, 1, tree->right_son, tokens);
	// pid[1] = fork1();
	// if (pid[1] == 0)
	// 	ft_piped_end(bibe, 0, tree->left_son, tokens);

// int	ft_piped_end(int *bibe, int io, t_tree *tree, t_token *tokens)
// {
// 	int	out;

// 	// printf("pipe \n");
// 	// if (tokens[tree->token_index].type > 21)
// 	// out = exec_redir(tree, tokens, 0, 1);
// 	if (io == 0)
// 	{
// 		if (ft_dup(bibe[0], STDIN_FILENO) < 0)
// 			exit (1);
// 	}
// 	else
// 	{
// 		if (ft_dup(bibe[1], STDOUT_FILENO) < 0)
// 			exit (1);
// 	}
// 	close(bibe[1]);
// 	// if (tokens[tree->token_index].type <= 21)
// 		out = exec_redir(tree, tokens, 1, 0);	
// 	close(bibe[0]);
// 		// out = exec_node(tree, tokens);
// 	// printf(" pout = %d \n", out);
// 	exit(out);
// }

int	pipe_out(int *bibe, t_tree *tree, t_token *tokens)
{
	int		out;
	int		pid;

	pid = fork1();
	if (pid == 0)
	{
		close(bibe[1]);
		if (ft_dup(bibe[0], STDIN_FILENO) < 0)
			exit (1);
		out = exec_node(tree, tokens);
		close(bibe[0]);
		free(bibe);
		exit(out);
	}
	return (pid);
}

int	pipe_in(int *bibe, t_tree *tree, t_token *tokens)
{
	int		out;
	int		pid;

	pid = fork1();
	if (pid == 0)
	{
		close(bibe[0]);
		if (ft_dup(bibe[1], STDOUT_FILENO) < 0)
			exit (1);
		out = exec_node(tree, tokens);
		close(bibe[1]);
		free(bibe);
		exit(out);
	}
	return (pid);
}

//     pipe
// 1  - - - >  0

int	ft_pipe(t_tree *tree, t_token *tokens)
{
	int		pid1;
	int		pid2;
	int		*bibe;
	int		out;
	int		out2;

	out = 0;
	out2 = 0;
	bibe = (int *) malloc(2 * sizeof(int));
	if (pipe(bibe) < 0)
		return (1);
	pid2 = pipe_in(bibe, tree->right_son, tokens);
	pid1 = pipe_out(bibe, tree->left_son, tokens);
	close(bibe[1]);
	close(bibe[0]);
	waitpid(pid2, &out2, 0);
	waitpid(pid1, &out, 0);
	free(bibe);
	return (out >> 8);
}
	// printf("\n out = %d | out2 = %d \n", out, out2);
