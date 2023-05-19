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

int	ft_redirect_in(t_tree *tree, t_token *tokens)
{
	int		fd;
	int		x;
	// t_tree	*cmd;

	// ft_printf("< %d\n", tree->token_index);
	// cmd = tree->right_son;
	// while (tokens[cmd->token_index].type > 21)
	// 	cmd = cmd->right_son;
	// if (fork1() == 0)
	// {
	x = tree->token_index;
	fd = open(tokens[x].args[0], O_RDONLY, 0600);
	if (fd < 0)
	{
		perror("couldnt open file");
		return (1);
	}
	if (ft_dup(fd, STDIN_FILENO) < 0)
		return (2);
	// exec_node(cmd, tokens);
	close(fd);
	// }
	// else if (tree->father && tokens[tree->father->token_index].type == 20)
	// 	exec_node(tree->right_son, tokens);
	// wait(NULL);
	return (0);
}

char	*here_doc(char *s, int *fd_out, int qt)
{
	int		*bibe;
	char	*input;

	bibe = (int *) malloc(2 * sizeof(int));
	if (pipe(bibe) < 0)
		return (0);
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strncmp(input, s, ft_strlen(input)) == 0)
			break ;
		if (*(input + count_space(input)))
		{
			if (qt == 1)
				input = replace_dollars(input);
			// printf("%s\n", input);
	        write(bibe[1], input, ft_strlen(input));
	        write(bibe[1], "\n", 1);
		}
		*fd_out = bibe[0];
		free(input);
	}
	close(bibe[1]);
	return (0);
}

int	ft_redirect_in_append(t_tree *tree, t_token *tokens)
{
	int		fd;
	int		x;
	char	*in;

	x = tree->token_index;
	in = here_doc(tokens[x].args[0], &fd, tokens[x].redir);
	// fd = open(tokens[x].args[0], O_RDONLY | O_APPEND, 0600);
	if (fd < 0)
	{
		perror("couldnt open file");
		return (1);
	}
	if (ft_dup(fd, STDIN_FILENO) < 0)
		return (2);
	close(fd);
	return (0);
}

int	ft_redirect_out(t_tree *tree, t_token *tokens)
{
	int		fd;
	int		x;

	x = tree->token_index;
	fd = open(tokens[x].args[0], O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd < 0)
	{	
		perror("couldnt open file");
		return (1);
	}
	if (ft_dup(fd, STDOUT_FILENO) < 0)
		return (2);
	close(fd);
	return (0);
}

int	ft_redirect_out_append(t_tree *tree, t_token *tokens)
{
	int	fd;
	int	x;

	x = tree->token_index;
	fd = open(tokens[x].args[0], O_WRONLY | O_CREAT | O_APPEND, 0600);
	if (fd < 0)
	{
		perror("couldnt open file");
		return (1);
	}
	if (ft_dup(fd, STDOUT_FILENO) < 0)
		return (2);
	close(fd);
	return (0);
}

int	exec_symbol(t_tree *tree, t_token *tokens)
{
	int	x;
	int	out;

	out = 1;
	x = tree->token_index;
	// ft_printf("x = %d\n", x);
	if (tokens[x].type == 21)
		out = ft_pipe(tree, tokens);
	else if (tokens[x].type == 22)
		out = ft_redirect_in_append(tree, tokens);
	else if (tokens[x].type == 23)
		out = ft_redirect_in(tree, tokens);
	else if (tokens[x].type == 24)
		out = ft_redirect_out_append(tree, tokens);
	else if (tokens[x].type == 25)
		out = ft_redirect_out(tree, tokens);
	return (out);
}
