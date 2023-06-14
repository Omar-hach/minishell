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

// void	free_args(t_tree *tree, t_token *tokens)
// {
// 	if (tree == NULL)
// 		return ;
// 	free_args(tree->right_son, tokens);
// 	free_args(tree->left_son, tokens);
// 	if (tokens[tree->token_index].args)
// 		free_aray(tokens[tree->token_index].args);
// }

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

void	free_tree(t_tree *root, t_token *nodes)
{
	if (root == NULL)
		return ;
	free_tree(root->right_son, nodes);
	free_tree(root->left_son, nodes);
	if (nodes[root->token_index].args)
		free_aray(nodes[root->token_index].args);
	free(root);
}
