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

	x = tree->token_index;
	fd = open(tokens[x].args[0], O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_printf("%s: No such file or directory\n", tokens[x].args[0]);
		return (1);
	}
	if (ft_dup(fd, STDIN_FILENO) < 0)
		return (1);
	close(fd);
	return (0);
}

int	ft_redirect_in_append(t_tree *tree, t_token *tokens)
{
	int		fd;
	int		x;

	x = tree->token_index;
	fd = open(tokens[x].args[0], O_RDONLY, 0644);
	if (fd < 0)
	{
		ft_printf("%s: No such file or directory\n", tokens[x].args[0]);
		return (1);
	}
	if (ft_dup(fd, STDIN_FILENO) < 0)
		return (1);
	close(fd);
	return (0);
}

int	ft_redirect_out(t_tree *tree, t_token *tokens)
{
	int		fd;
	int		x;

	x = tree->token_index;
	fd = open(tokens[x].args[0], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{	
		ft_printf("%s: No such file or directory\n", tokens[x].args[0]);
		return (1);
	}
	if (ft_dup(fd, STDOUT_FILENO) < 0)
		return (1);
	close(fd);
	return (0);
}

int	ft_redirect_out_append(t_tree *tree, t_token *tokens)
{
	int	fd;
	int	x;

	x = tree->token_index;
	fd = open(tokens[x].args[0], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		ft_printf("%s: No such file or directory\n", tokens[x].args[0]);
		return (1);
	}
	if (ft_dup(fd, STDOUT_FILENO) < 0)
		return (1);
	close(fd);
	return (0);
}

int	exec_symbol(t_tree *tree, t_token *tokens, char **env)
{
	int	x;
	int	out;

	out = 0;
	x = tree->token_index;
	if (tokens[x].type == 21)
		out = ft_pipe(tree, tokens, env);
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
