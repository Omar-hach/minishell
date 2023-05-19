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

t_tree	*new_branch(int data)
{
	t_tree	*tree;

	tree = (t_tree *)ft_calloc(1, sizeof(t_tree));
	tree->token_index = data;
	tree->father = NULL;
	tree->left_son = NULL;
	tree->right_son = NULL;
	return (tree);
}

void	treeprint(t_tree *root, int level, t_token *nodes)
{
	int	i;

	i = 7;
	if (root == NULL)
		return ;
	level += 8;
	treeprint(root->right_son, level, nodes);
	ft_printf("\n");
	while (++i < level)
	{
		ft_printf(" ");
	}
	ft_printf("%d=%s-->left=%p-->right=%p\n", nodes[root->token_index].type, nodes[root->token_index].arg, root->left_son, root->right_son);
	treeprint(root->left_son, level, nodes);
	//free(root);
}

t_tree	*create_tree(t_token *nodes, int len)
{
	t_tree	*branch;
	t_tree	*root;
	t_tree	*tree;
	int		*list;
	int		i;

	i = -1;
	list = (int *)ft_calloc(len + 1, sizeof(int));
	list[len] = -1;
	list[len + 1] = -1;
	while (list[++i] > -1)
		list[i] = nodes[i].type;
	i = 0;
	root = new_branch(i++);
	while (list[i] > -1)
	{
		branch = new_branch(i);
			// ft_printf("list=%d = ",list[root->token_index]);
		if (list[i] < 19)
		{
			if (!root->left_son)
				root->left_son = branch;
			else
				root->right_son = branch;
			branch->father = root;
		}
		if (list[i] == 22 || list[i] == 23)
		// if (list[i] > 21)
		{
			while (root->father && list[root->father->token_index] == 21)
				root = root->father;
			if (list[root->token_index] != 21)
				list[i] = 26;
			else
			{
				// ft_printf("here\n");
				branch->father = root;
				branch->right_son = root->left_son;
				root->left_son = branch;
				branch->right_son->father = branch;
			}
		}
		if (list[i] == 21 || list[i] > 23)
		{
			// if(list[i] > 23)
			// {
				// while (root->father && list[root->father->token_index] == 21)
				// root = root->father;
			// }
			// else
			// {
			// 	while (root->father)
			// 		root = root->father;
			// }
			// if(list[i] > 23)
				while (root->father)
					root = root->father;
			root->father = branch;
			branch->right_son = root;
		}
		root = branch;
		i++;
	}
	tree = root;
	while (tree->father)
		tree = tree->father;
	free(list);
	return (tree);
}

/*
        1=/bin/cat-->left=0x0-->right=0x0
21=(null)-->left=0x7fb159f041a0-->right=0x7fb159f040d0
        1=/bin/ls-->left=0x7fb159f041c0-->right=0x0
                23=file-->left=0x0-->right=0x0
<banch[23]=0x7fb159f041c0 root[1]->father[]=0x7fb159f041a0>
<banch[23]=0x7f9dbdf041c0 root[1]->father[]=0x7f9dbdf041a0>
        1=/bin/ls-->left=0x0-->right=0x0
21=(null)-->left=0x7f9dbdf041a0-->right=0x7f9dbdf040d0
        1=/bin/cat-->left=0x7f9dbdf041c0-->right=0x0
                23=file-->left=0x0-->right=0x0
<banch[23]=0x7f9dbdf041c0 root[1]->father[]=0x7f9dbdf041a0>*/
