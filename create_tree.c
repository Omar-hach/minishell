/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 16:22:33 by ohachami          #+#    #+#             */
/*   Updated: 2023/05/06 16:22:37 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_tree *new_branch(int data)
{
	t_tree	*tree;

	tree = (t_tree *)ft_calloc(1, sizeof(t_tree));
	tree->token_index = data;
	tree->father = NULL;
	tree->left_son = NULL;
	tree->right_son = NULL;
	return (tree);
}
t_tree *create_tree(t_token *nodes, int len)
{
	t_tree	*branch;
	t_tree	*root;
	t_tree	*tree;
	int		*list;
	int		i;

	i = -1;
	list = (int *)ft_calloc(len + 1, sizeof(int));
	list[len] = -1;
	while (list[++i] > -1)
		list[i] = nodes[i].type;
	i = 0;
	root = new_branch(i++);
	while (list[i] > -1)
	{
		branch = new_branch(i);
		if(list[i] == 21)
		{
			while(root->father)
				root = root->father;
			root->father = branch;
			branch->right_son = root;
		}
		else
		{
			root->left_son = branch;
			branch->father = root;
		}
		root = branch;
		i++;
	}
	tree = root;
	while(tree->father)
		tree = tree->father;
	free(list);
	return (tree);
}

