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
	{
		// printf("[%d] words = %p, %s\n",i, words[i], words[i]);
		free(words[i]);
	}
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

// char	*set_cmd(char *word, int *token, char *cmd, t_lexic lex)
// {
// 	char	*arg;
// 	char	*bin;

// 	if(ft_strncmp(cmd, "..", 2))
// 		bin = find_path(cmd, -1, -1, -1);
// 	if (ft_find(cmd, lex.l_cmd)
// 		&& ft_strlen(lex.l_cmd[ft_find(cmd, lex.l_cmd) - 1]) == ft_strlen(cmd))
// 		*token = ft_find(cmd, lex.l_cmd) + 10;
// 	else if (ft_strchr(cmd, '/'))
// 	{
// 		*token = 1;
// 		arg = (char *)ft_calloc(ft_strlen(word) + 1, sizeof(char));
// 		ft_memcpy(arg, word, ft_strlen(word) + 1);
// 		return (arg);
// 	}
// 	else if (bin)
// 	{
// 		*token = 1;
// 		free(bin);
// 		return (expand_cmd(cmd, bin, word));
// 	}
// 	if (bin)
// 		free(bin);
// 	return (NULL);
// }
// //echo "hello    ">a   b   c --> cat a : helo b c
// char	*cmd_split(char *word, int *token, t_lexic lex)
// {
// 	int		i;
// 	int		j;
// 	char	*cmd;
// 	char	*arg;

// 	i = 0;
// 	j = 0;
// 	cmd = NULL;
// 	word += count_space(word);
// 	word = replace_dollars(word); //$ management
// 	if (ft_find(word, lex.l_symb)) //probleme here
// 		cmd = fill_symb(word, &i, token, ft_find(word, lex.l_symb));
// 	else
// 		cmd = fill_cmd(word, j, &i);
// 	if (!cmd || *token == 21)
// 		return (NULL);
// 	//token detection
// 	//ft_printf("word=%d.\n",  *token);
// 	arg = set_cmd(word, token, cmd, lex);
// 	if (*token < 1)
// 	{
// 		ft_printf("minshell: %s :command not found\n", cmd);
// 		*error = 127;
// 		free(cmd);
// 		return (NULL);
// 	}
// 	//fill arg
// 	arg = fill_arg(word, i);
// 	//free the rest
// 	// if (!arg)
// 	free(cmd);
// 	return (arg);
// }