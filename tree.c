/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:46:38 by yhachami          #+#    #+#             */
/*   Updated: 2023/04/28 15:46:50 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	exec_prog(t_token token)
{
	char	*prog_name;
	char	**prog_argv;
	char	**prog_envp = NULL;
	//char	*prog_envp[] = { "some", "environment", NULL };

	prog_argv = ft_split(token.arg, ' ');
	prog_name = ft_strdup(prog_argv[0]);
	execve(prog_name, prog_argv, prog_envp);
}

int	exec_node(t_tree *tree, t_token *tokens)
{
	int	x;
	int	out;

	x = tree->token_index;
	// ft_printf("node %d\n", x);
	// ft_printf("type = %d , arg = %s\n",tokens[x].type, tokens[x].arg);
	if (tokens[x].type == 1)
		exec_prog(tokens[x]);
	else if (tokens[x].type / 10 == 1)
		out = exec_cmd(tokens[x]);
	else if (tokens[x].type / 10 == 2)
		out = exec_symbol(tree ,tokens);
	return (out);
}

void	read_tree(t_tree *tree, t_token *tokens)
{
	int	x;

	while (tree->left_son)
		tree = tree->left_son;
	if (tree->father && tree->father->right_son)
		tree = tree->father;
	// printf("node %d\n", tree->token_index);
	while (tree)
	{
		exec_node(tree, tokens);
		tree = tree->father;
	}
}

//              0
//             / \
//            /   \
//           1     2
//          /\
//         /  
//        3     
//       / \
//      /   \
//     5     4

// ls | grep a > file1 | grep .c

int main() {
	t_tree	*tree;
	t_token	*tokens;

	tree = (t_tree *) malloc(sizeof(t_tree));
	tree->token_index = 0;

	tree->father = NULL;
	// tree->right_son = NULL;
	// tree->left_son = NULL;

	tree->right_son = (t_tree *) malloc(sizeof(t_tree));
	tree->right_son->token_index = 2;
	tree->right_son->father = tree;
	tree->right_son->right_son = 0;
	tree->right_son->left_son = 0;

	tree->left_son = (t_tree *) malloc(sizeof(t_tree));
	tree->left_son->token_index = 1;
	tree->left_son->father = tree;

	tree->left_son->right_son = 0;
	// tree->left_son->left_son = 0;

	// tree->left_son->right_son = (t_tree *) malloc(sizeof(t_tree));
	// tree->left_son->right_son->token_index = 4;
	// tree->left_son->right_son->father = tree->left_son;
	// tree->left_son->right_son->right_son = 0;
	// tree->left_son->right_son->left_son = 0;

	tree->left_son->left_son = (t_tree *) malloc(sizeof(t_tree));
	tree->left_son->left_son->token_index = 3;
	tree->left_son->left_son->father = tree->left_son;
	// tree->left_son->left_son->right_son = 0;

	// tree->left_son->left_son->left_son = 0;

	tree->left_son->left_son->left_son = (t_tree *) malloc(sizeof(t_tree));
	tree->left_son->left_son->left_son->token_index = 5;
	tree->left_son->left_son->left_son->father = tree->left_son->left_son;
	tree->left_son->left_son->left_son->right_son = 0;
	tree->left_son->left_son->left_son->left_son = 0;

	tree->left_son->left_son->right_son = (t_tree *) malloc(sizeof(t_tree));
	tree->left_son->left_son->right_son->token_index = 4;
	tree->left_son->left_son->right_son->father = tree->left_son->left_son;
	tree->left_son->left_son->right_son->right_son = 0;
	tree->left_son->left_son->right_son->left_son = 0;

	// ft_printf("treeed");

	tokens = (t_token *) malloc(7 * sizeof(t_token));
	tokens[0].type = 11;
	tokens[0].arg = 0;
	// tokens[0].arg = ft_strdup("VR=not ok=ok notok=yetok");
	// tokens[0].arg = ft_strdup("/bin/ls");
	tokens[0].in = 0;
	tokens[0].out = 1;

	tokens[1].type = 21;
	// tokens[1].arg = 0;
	tokens[1].arg = ft_strdup("file1");
	tokens[1].in = 0;
	tokens[1].out = 1;

	tokens[2].type = 1;
	// tokens[2].arg = 0;
	tokens[2].arg = ft_strdup("/usr/bin/grep a");
	tokens[2].in = 0;
	tokens[2].out = 1;

	tokens[3].type = 20;
	// tokens[3].arg = 0;
	// tokens[3].arg = ft_strdup("");
	tokens[3].in = 0;
	tokens[3].out = 1;

	tokens[4].type = 1;
	//tokens[2].arg = 0;
	tokens[4].arg = ft_strdup("/usr/bin/grep Apr");
	tokens[4].in = 0;
	tokens[4].out = 1;

	tokens[5].type = 1;
	//tokens[2].arg = 0;
	tokens[5].arg = ft_strdup("/bin/ls -l");
	tokens[5].in = 0;
	tokens[5].out = 1;

	return (exec_node(tree, tokens));
}
