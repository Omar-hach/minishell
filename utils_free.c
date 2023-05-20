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
	while (words[++i]){
	ft_printf("\n------%p--%s---\n", words[i], words[i]);
		free(words[i]);}
	free(words);
	return (NULL);
}

void	*free_struct_array(char **words, t_lexic *lex, t_token *nodes, int len)
{
	int	i;

	i = -1;
	while (nodes && nodes[++i].arg && i < len)
		free(nodes[i].arg);
	if (nodes)
		free(nodes);
	if (words){
		free_aray(words);}
	if (lex && lex->l_cmd)
		free_aray(lex->l_cmd);
	if (lex && lex->l_symb)
		free_aray(lex->l_symb);
	return (NULL);
}

void	free_tree(t_tree *root)
{
	if (root == NULL)
		return ;
	free_tree(root->right_son);
	free_tree(root->left_son);
	free(root);
}
