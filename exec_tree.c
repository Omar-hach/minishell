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

int	exec_prog(t_token token, char **env)
{
	int			out;

	out = check_file(token.args[0]);
	if (out)
		return (out);
	if (fork1() == 0)
	{
		handle_signals();
		out = execve(token.args[0], token.args, env);
	}
	wait(&out);
	return (out >> 8);
}

int	exec_token(t_tree *tree, t_token *tokens, char **env)
{
	int	x;
	int	out;

	out = 0;
	x = tree->token_index;
	if (tokens[x].type == 1)
		out = exec_prog(tokens[x], env);
	else if (tokens[x].type / 10 == 1)
		out = exec_cmd(tree, tokens, x, env);
	else if (tokens[x].type / 10 == 2)
		out = exec_symbol(tree, tokens, env);
	return (out);
}

int	exec_redir(t_tree *tree, t_token *tokens, char **env)
{
	t_tree	*cmd;
	t_tree	*redir;
	int		out;

	out = 0;
	cmd = NULL;
	redir = tree;
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
		out = exec_token(redir, tokens, env);
		if (out)
			exit(out);
		redir = redir->father;
	}
	if (cmd)
		out = exec_token(cmd, tokens, env);
	return (out);
}

int	exec_node(t_tree *tree, t_token *tokens, char **env)
{
	int		x;
	int		out;

	out = 0;
	x = tree->token_index;
	if (tokens[x].type > 21)
	{
		if (fork1() == 0)
		{
			out = exec_redir(tree, tokens, env);
			exit(out);
		}
		wait(&out);
		out = out >> 8;
	}
	else
		out = exec_token(tree, tokens, env);
	return (out);
}

int	exec_tree(t_tree *tree, t_token *tokens, char **env)
{
	make_heredocs(tree, tokens);
	signal(SIGINT, SIG_IGN);
	if (*g_error != 130)
		*g_error = exec_node(tree, tokens, env);
	handle_signals();
	remove_heredocs(tree, tokens);
	free_tree(tree, tokens);
	free(tokens);
	return (*g_error);
}
/*
//    ls | grep a 
//
//              0   |
//             / \
//            /   \
//     grep  3     2  ls

//
// ls | grep a < file1 > file2
//
//           4  > file2    
//            \
//             \
//              0  |  
//             / \
//            /   \
//      ls   1     3  < file1
//                  \
//                   \
//                    2  grep
//   

//		
// ls | grep a < file1 < file2
//
//              0   |
//             / \
//            /   \
//  < file1  3     2  ls
//            \
//             \
//    < file2   4
//               \
//                \
//      grep a     1 
//

//
// ls | grep c | grep o
//
//              0 
//             / \
//            /   \
//           1     2
//                / \
//               /   \
//              3     4   ls
//
*/
