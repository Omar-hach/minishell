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

int	exec_token(t_tree *tree, t_token *tokens)
{
	int	x;
	int	out;

	out = 1;
	x = tree->token_index;
	if (tokens[x].type == 1)
		exec_prog(tokens[x]);
	else if (tokens[x].type / 10 == 1)
		out = exec_cmd(tokens[x]);
	else if (tokens[x].type / 10 == 2)
		out = exec_symbol(tree ,tokens);
	return (out);
}

int	exec_node(t_tree *tree, t_token *tokens)
{
	int	x;
	int	out;
	// int	redir;
	// t_tree *cmd;

	out = 0;
	x = tree->token_index;
	// ft_printf("node %d : type = %d , arg = %s\n",x,tokens[x].type, tokens[x].arg);
	// redir = tokens[x].in;
	// if (redir > -1)
	// {
	// 	cmd = tree;
	// 	redir = tokens[x].in;
	// 	while (redir != cmd->token_index)
	// 		cmd = cmd->left_son;
	// 	if (fork1() == 0)
	// 		out = exec_node(cmd, tokens);
	// 	wait(NULL);
	// 	cmd = tree;
	// 	redir = tokens[x].in;
	// 	while (redir != cmd->token_index)
	// 	{
	// 		out = exec_token(cmd, tokens);
	// 		cmd = cmd->left_son;
	// 	}
	// }
	// if (tokens[x].type == 1 && !tree->father)
	// {
	// 	if (fork1() == 0)
	// 		out = exec_token(tree, tokens);
	// 	wait(NULL);
	// }
	// else
		out = exec_token(tree, tokens);
		// ft_printf("node %d finished\n",x);
	return (out);
}

void	read_tree(t_tree *tree, t_token *tokens)
{
	// int	x;

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


// ls | grep a < file1 <file2
//
//              0       
//             / \
//            /   \
//           2     1
//                /
//               /
//              3
//             /   
//            /
//           4    
//                 
//   

// /bin/ls | /usr/bin/grep c | /usr/bin/grep o
//
//              0 
//             / \
//            /   \
//           2     1
//                / \
//               /   \
//              4     3



// int main() {
// 	t_tree	*tree;
// 	t_token	*tokens;

// 	tree = (t_tree *) malloc(sizeof(t_tree));
// 	tree->token_index = 0;
// 	tree->father = NULL;
// 	// tree->right_son = NULL;
// 	// tree->left_son = NULL;

// 	tree->right_son = (t_tree *) malloc(sizeof(t_tree));
// 	tree->right_son->token_index = 1;
// 	tree->right_son->father = tree;
// 	// tree->right_son->right_son = 0;
// 	// tree->right_son->left_son = 0;

// 	tree->left_son = (t_tree *) malloc(sizeof(t_tree));
// 	tree->left_son->token_index = 2;
// 	tree->left_son->father = tree;
// 	tree->left_son->right_son = 0;
// 	tree->left_son->left_son = 0;

// 	tree->right_son->right_son = (t_tree *) malloc(sizeof(t_tree));
// 	tree->right_son->right_son->token_index = 3;
// 	tree->right_son->right_son->father = tree->right_son;
// 	tree->right_son->right_son->right_son = 0;
// 	tree->right_son->right_son->left_son = 0;

// 	tree->right_son->left_son = (t_tree *) malloc(sizeof(t_tree));
// 	tree->right_son->left_son->token_index = 4;
// 	tree->right_son->left_son->father = tree->right_son;
// 	tree->right_son->left_son->right_son = 0;
// 	tree->right_son->left_son->left_son = 0;

// 	// tree->right_son->right_son->left_son = (t_tree *) malloc(sizeof(t_tree));
// 	// tree->right_son->right_son->left_son->token_index = 3;
// 	// tree->right_son->right_son->left_son->father = tree->left_son->left_son;
// 	// tree->right_son->right_son->left_son->right_son = 0;
// 	// tree->right_son->right_son->left_son->left_son = 0;

// 	// tree->right_son->left_son->left_son = (t_tree *) malloc(sizeof(t_tree));
// 	// tree->right_son->left_son->left_son->token_index = 4;
// 	// tree->right_son->left_son->left_son->father = tree->right_son->left_son->left_son;
// 	// tree->right_son->left_son->left_son->right_son = 0;
// 	// tree->right_son->left_son->left_son->left_son = 0;

// 	// tree->left_son->right_son->left_son = (t_tree *) malloc(sizeof(t_tree));
// 	// tree->left_son->right_son->left_son->token_index = 5;
// 	// tree->left_son->right_son->left_son->father = tree->left_son->left_son;
// 	// tree->left_son->right_son->left_son->right_son = 0;
// 	// tree->left_son->right_son->left_son->left_son = 0;

// 	// tree->left_son->right_son->right_son = (t_tree *) malloc(sizeof(t_tree));
// 	// tree->left_son->right_son->right_son->token_index = 3;
// 	// tree->left_son->right_son->right_son->father = tree->left_son->left_son;
// 	// tree->left_son->right_son->right_son->right_son = 0;
// 	// tree->left_son->right_son->right_son->left_son = 0;


// 	// tree->left_son->left_son->left_son = (t_tree *) malloc(sizeof(t_tree));
// 	// tree->left_son->left_son->left_son->token_index = 4;
// 	// tree->left_son->left_son->left_son->father = tree->left_son->left_son;
// 	// tree->left_son->left_son->left_son->right_son = 0;
// 	// tree->left_son->left_son->left_son->left_son = 0;

// 	// tree->left_son->left_son->right_son = (t_tree *) malloc(sizeof(t_tree));
// 	// tree->left_son->left_son->right_son->token_index = 4;
// 	// tree->left_son->left_son->right_son->father = tree->left_son->left_son;
// 	// tree->left_son->left_son->right_son->right_son = 0;
// 	// tree->left_son->left_son->right_son->left_son = 0;

// 	// ft_printf("treeed");

// 	tokens = (t_token *) malloc(7 * sizeof(t_token));
// 	tokens[0].type = 21;
// 	tokens[0].arg = 0;
// 	// tokens[0].arg = ft_strdup("VR=not ok=ok notok=yetok");
// 	// tokens[0].arg = ft_strdup("file1");
// 	tokens[0].in = -1;
// 	tokens[0].out = 1;

// 	tokens[1].type = 21;
// 	tokens[1].arg = 0;
// 	// tokens[1].arg = ft_strdup("/bin/ls ");
// 	tokens[1].in = -1;
// 	tokens[1].out = 1;

// 	tokens[2].type = 1;
// 	// tokens[2].arg = ft_strdup("/usr/bin/grep a");
// 	tokens[2].arg = ft_strdup("/usr/bin/grep o");
// 	tokens[2].in = 4;
// 	tokens[2].out = 1;

// 	tokens[3].type = 1;
// 	// tokens[3].arg = 0;
// 	tokens[3].arg = ft_strdup("/bin/ls");
// 	tokens[3].in = 0;
// 	tokens[3].out = 1;

// 	tokens[4].type = 1;
// 	//tokens[2].arg = 0;
// 	tokens[4].arg = ft_strdup("/usr/bin/grep c");
// 	tokens[4].in = -1;
// 	tokens[4].out = 1;

// 	tokens[5].type = 1;
// 	//tokens[2].arg = 0;
// 	tokens[5].arg = ft_strdup("/usr/bin/grep Apr");
// 	tokens[5].in = 0;
// 	tokens[5].out = 1;

// 	return (exec_node(tree, tokens));
// }