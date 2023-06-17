/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 09:42:48 by yhachami          #+#    #+#             */
/*   Updated: 2023/06/11 09:42:51 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// make all the heredoc files in the tree
int	make_heredocs(t_tree *tree, t_token *tokens)
{
	int		out;
	int		x;

	out = 0;
	x = tree->token_index;
	if (tokens[x].type == 22)
		out = here_file(tokens[x].args[0], tokens[x].qt);
	if (tree->right_son)
		out = make_heredocs(tree->right_son, tokens);
	if (tree->left_son)
		out = make_heredocs(tree->left_son, tokens);
	return (out);
}

// remove all the heredoc files in the tree
int	remove_heredocs(t_tree *tree, t_token *tokens)
{
	int		out;

	out = 0;
	if (tokens[tree->token_index].type == 22)
		out = unlink(tokens[tree->token_index].args[0]);
	if (tree->right_son)
		out = remove_heredocs(tree->right_son, tokens);
	if (tree->left_son)
		out = remove_heredocs(tree->left_son, tokens);
	return (out);
}

int	get_min_len(char *s1, char *s2)
{
	if (ft_strlen(s1) > ft_strlen(s2))
		return (ft_strlen(s1));
	else
		return (ft_strlen(s2));
}

int	heredoc_prompt(int fd, char *input, char *s, int qt)
{
	char	*tmp;

	input = readline("> ");
	if (!input[0] || !s || ft_strncmp(input, s, get_min_len(s, input)) == 0)
	{
		free(input);
		return (0);
	}
	if (*(input + count_space(input)))
	{
		if (qt == 0)
		{
			tmp = replace_dollars(input);
			free(input);
			input = tmp;
		}
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
	}
	free(input);
	return (1);
}

// creat file and open prompt for the heredoc files
int	here_file(char *s, int qt)
{
	int		fd;
	char	*input;
	int		x;

	if (fork1() == 0)
	{
		handle_heredoc_signals();
		unlink(s);
		fd = open(s, O_WRONLY | O_CREAT, 0644);
		if (fd < 0)
			return (-1);
		input = NULL;
		x = 1;
		while (x)
			x = heredoc_prompt(fd, input, s, qt);
		close(fd);
		exit(0);
	}
	wait(NULL);
	return (0);
}
