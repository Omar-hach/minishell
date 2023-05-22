/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:46:38 by yhachami          #+#    #+#             */
/*   Updated: 2023/04/28 15:46:50 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	exec_prog(t_token token)
{
	int		out;
	char	**prog_envp = NULL;
	DIR		*dir;
	//char	*prog_envp[] = { "some", "environment", NULL };

	// prog_argv = ft_split(token.arg, ' ');
	int len = ft_strlen(token.args[0]) - 1;
	if (token.args[0][len] == '.')
	{
		ft_printf(" .: filename argument required\n");
		*error = 2;
		return (2);
	}
	else
	{
		dir = opendir(token.args[0]);
		if (dir)
		{
			*error = 126;
			ft_printf(" %s: is a directory\n", token.args[0]);
			return (126);
		}
	}
	if (access(token.args[0], X_OK) != 0)
	{
		*error = 127;
		ft_printf(" %s: No such file or directory\n", token.args[0]);
		return (127);
	}
	if (fork1() == 0)
		out = execve(token.args[0], token.args, prog_envp);
	wait(&out);
	// free(prog_argv);
	// printf("ooo %d %d\n", out, *error);
	if (out < 0)
		return (0);
	else
		return (out >> 8);
}

int	exec_token(t_tree *tree, t_token *tokens)
{
	int	x;
	int	out;

	out = 0;
	x = tree->token_index;
	// printf("node %d : type = %d , arg = %s\n\n",x,tokens[x].type, tokens[x].arg);
	tokens[x].args = arg_split(tokens[x].arg, " 	");
	if (tokens[x].args)
	{
		ft_skip(tokens, x);
		// int i = -1;
		// while (tokens[x].args[++i])
		// 	ft_printf("skipeed %d = %s\n",i,  tokens[x].args[i]);
	}
	if (tokens[x].type == 1)
		out = exec_prog(tokens[x]);
	else if (tokens[x].type / 10 == 1)
		out = exec_cmd(tokens[x]);
	else if (tokens[x].type / 10 == 2)
		out = exec_symbol(tree ,tokens);
	// printf("%d token = %s = %d\n", out , tokens[x].arg, tokens[x].type);
	return (out);
}

int	exec_redir(t_tree *tree, t_token *tokens)
{
	t_tree	*cmd;
	t_tree	*redir;
	int		out;

	if (fork1() == 0)
	{
		redir = tree;
		while (redir->right_son && tokens[redir->token_index].type > 21)
			redir = redir->right_son;
		cmd = redir;
		if (redir->father)
			redir = redir->father;
		while (redir && tokens[redir->token_index].type > 21)
		{
			// ft_printf("<^> %d\n", redir->token_index);
			out = exec_token(redir, tokens);
			// printf("reee 1 = %d",out);
			if (out)
				exit(out);
			redir = redir->father;
		}
		out = exec_token(cmd, tokens);
		// printf("reee 2 = %d",out);
		exit(out);
	}
	wait(&out);
	return (out >> 8);
}

int	exec_node(t_tree *tree, t_token *tokens)
{
	int		x;
	int		out;

	out = 0;
	x = tree->token_index;
	// if (tokens[x].type == 1 && !tree->father)
	// {
	// 	if (fork1() == 0)
	// 		out = exec_token(tree, tokens);
	// 	wait(&out);
	// }
	if (tokens[x].type > 21)
		out = exec_redir(tree, tokens);
	else
		out = exec_token(tree, tokens);
	// if (out > 2 && out != 127)
	// 	*error = 1;
	// else if (out != 0)
		*error = out;
	// if (tokens[x].arg)
	// 	free(tokens[x].arg);
	if (tokens[x].args)
		free_aray(tokens[x].args);
	// printf("%d out = %d %d \n",x, out , *error);
	// ft_printf("node %d finished = %d\n",x,out);
	return (*error);
}

// ls | grep a < file1 > file2
//
//           4   file2    
//            \
//             \
//              0    
//             / \
//            /   \
//      ls   1     3  file1
//                  \
//                   \
//                    2  grep
//                 
//   

//		
// ls | grep a < file1 < file2
//
//              0       
//             / \
//            /   \
//    file1  3     2
//            \
//             \
//      file2   4
//               \
//                \
//                 1 
//
//

//
// /bin/ls | /usr/bin/grep c | /usr/bin/grep o
//
//              0 
//             / \
//            /   \
//           1     2
//                / \
//               /   \
//              3     4   ls
//



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
