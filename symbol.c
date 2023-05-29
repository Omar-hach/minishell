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

int	here_doc(char *s, int qt)
{
	int		*bibe;
	char	*input;

	bibe = (int *) malloc(2 * sizeof(int));
	if (pipe(bibe) < -1)
		return (0);
	while (1)
	{
		ft_printf(">>> MiniShell $> ");
		input = get_next_line(0);
		input[ft_strlen(input) - 1] = '\0';
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

int	ft_redirect_in_append(t_tree *tree, t_token *tokens)
{
	int		fd;
	int		x;

	// printf("<<\n");
	x = tree->token_index;
	fd = here_doc(tokens[x].args[0], tokens[x].qt);
	// tokens[x].redir[1] = fd;
	// fd = open(tokens[x].args[0], O_RDONLY | O_APPEND, 0644);
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

int	exec_symbol(t_tree *tree, t_token *tokens)
{
	int	x;
	int	out;

	out = 0;
	x = tree->token_index;
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
