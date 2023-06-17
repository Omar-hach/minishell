/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 01:49:46 by ohachami          #+#    #+#             */
/*   Updated: 2023/05/13 01:49:48 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_aray(char	**words)
{
	int	i;

	i = -1;
	while (words[++i])
		free(words[i]);
	free(words);
	return (NULL);
}

void	exit_outside(int x, t_tree *tree, t_token *tokens)
{
	free_tree(tree, tokens);
	free(tokens);
	free(g_error);
	exit(x);
}

void	free_env(char **env)
{
	int			x;

	x = -1;
	while (env[++x])
		free(env[x]);
}

void	*free_struct_array(char **words, t_lexic *lex, t_token *nodes, int len)
{
	int	i;

	i = -1;
	while (nodes && nodes[++i].args && i < len)
		free_aray(nodes[i].args);
	if (words)
		free_aray(words);
	if (lex && lex->l_cmd)
		free_aray(lex->l_cmd);
	if (nodes)
		free(nodes);
	if (lex && lex->l_symb)
		free_aray(lex->l_symb);
	return (NULL);
}

void	free_tree(t_tree *tree, t_token *nodes)
{
	if (tree == NULL)
		return ;
	free_tree(tree->right_son, nodes);
	free_tree(tree->left_son, nodes);
	if (nodes[tree->token_index].args)
		free_aray(nodes[tree->token_index].args);
	free(tree);
}
