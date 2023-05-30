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
	char	**prog_envp;

	prog_envp = NULL;
	out = check_file(token.args[0]);
	if (out)
		return (out);
	if (fork1() == 0)
		out = execve(token.args[0], token.args, prog_envp);
	wait(&out);
	// printf("ooo %d %d\n", out, *error);
	return (out >> 8);
}

int	exec_token(t_tree *tree, t_token *tokens)
{
	int	x;
	int	out;

	out = 0;
	x = tree->token_index;
	// printf("------ node %d : type = %d , arg = %s out = %d\n",x,tokens[x].type, tokens[x].arg , out);
	if (tokens[x].type == 1)
		out = exec_prog(tokens[x]);
	else if (tokens[x].type / 10 == 1)
		out = exec_cmd(tokens[x]);
	else if (tokens[x].type / 10 == 2)
		out = exec_symbol(tree, tokens);
	return (out);
}

int	make_heredocs(t_tree *tree, t_token *tokens)
{
	int		out;
	int		x;

	out = 0;
	x = tree->token_index;

	if (tokens[tree->token_index].type == 22)
		out = here_file(tokens[x].args[0], tokens[x].qt);
	if (tree->right_son)
		out = make_heredocs(tree->right_son, tokens);
	if (tree->left_son)
		out = make_heredocs(tree->left_son, tokens);
	return (out);
}

int	remove_heredocs(t_tree *tree, t_token *tokens)
{
	int		out;

	out = 0;
	if (tokens[tree->token_index].type == 22)
		unlink(tokens[tree->token_index].args[0]);
	if (tree->right_son)
		out = remove_heredocs(tree->right_son, tokens);
	if (tree->left_son)
		out = remove_heredocs(tree->left_son, tokens);
	return (out);
}

int	exec_redir(t_tree *tree, t_token *tokens, int xcmd, int xredir)
{
	t_tree	*cmd;
	t_tree	*redir;
	int		out;

	out = 0;
	cmd = NULL;
	redir = tree;
	// make_heredocs(tree, tokens);
	while (redir->right_son && tokens[redir->token_index].type > 21)
		redir = redir->right_son;
	if (tokens[redir->token_index].type <= 21)
	{
		cmd = redir;
		if (redir->father)
			redir = redir->father;
	}
	while (redir && tokens[redir->token_index].type > 21)
	{
		// printf("redir = %d > %s\n", redir->token_index, tokens[redir->token_index].arg);
		if (xredir == 1)
			out = exec_token(redir, tokens);
		if (out)
			exit(out);
		redir = redir->father;
	}
	if (cmd && xcmd == 1)
		out = exec_token(cmd, tokens);
	return (out);
}

int	here_file(char *s, int qt)
{
	int		tmp;
	char	*input;

	tmp = open(s, O_WRONLY | O_CREAT, 0644);
	if (tmp < 0)
		return (-1);
	while (1)
	{
		input = readline("> ");
		if (!input || !s || ft_strncmp(input, s, ft_strlen(input)) == 0)
			break ;
		if (*(input + count_space(input)))
		{
			if (qt == 0)
				input = replace_dollars(input);
	        write(tmp, input, ft_strlen(input));
	        write(tmp, "\n", 1);
		}
		free(input);
	}
	close(tmp);
	// printf("<< end\n");
	return (0);
}

int	exec_node(t_tree *tree, t_token *tokens)
{
	int		x;
	int		out;

	out = 0;
	x = tree->token_index;
	if (tokens[x].type > 21)
	{
		if (fork1() == 0)
		{
			out = exec_redir(tree, tokens, 1, 1);
			exit(out);
		}
		wait(&out);
		out = out >> 8;
	}
	else
		out = exec_token(tree, tokens);
	// ft_printf("node %d finished = %d error = %d\n",x,out, *error);
	return (out);
}

int	exec_tree(t_tree *tree, t_token *tokens)
{
	make_heredocs(tree, tokens);
	*error = exec_node(tree, tokens);
	remove_heredocs(tree, tokens);
	// if (tokens[x].arg)
	// 	free(tokens[x].arg);
	// if (tokens[x].args)
	// 	free_aray(tokens[x].args);
	return (*error);
}
//
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
