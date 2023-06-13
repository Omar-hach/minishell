/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 01:53:28 by ohachami          #+#    #+#             */
/*   Updated: 2023/05/13 01:53:31 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_token	*malloc_nodes(t_token *nodes, int len, t_lexic *lex)
{
	int	i;

	i = -1;
	nodes = (t_token *)ft_calloc(len, sizeof(t_token));
	if (!nodes)
		return (free_struct_array(NULL, lex, nodes, 0));
	while (++i < len)
	{
		nodes[i].type = 0;
		nodes[i].args = NULL;
		nodes[i].qt = -1;
	}
	return (nodes);
}

int	nodes_count(char **word)
{
	int	i;

	i = 0;
	while (word[i])
		i++;
	return (i);
}

// printf("*word[%p]=%s *arg[%p]=%s  args = %s , i=%d\n",words, words[i], nodes[j].arg, nodes[j].arg, nodes[j].args[i] , i);
t_token	*fill_nodes(char **words, t_lexic *lex, t_token *nodes,  int *len)
{
	int		i;
	int		j;
	char	*arg;

	i = -1;
	j = 0;
	if (!nodes)
		*len = -1;
	while (words[++i] && nodes)
	{
			// printf("word = %s, type = %d\n",words[i], nodes[j].type);
		arg = cmd_split(words[i], &nodes[j].type, *lex);
		nodes[j].args = arg_split(arg, " 	");
		if (nodes[j].args)
			ft_skip(nodes, j);
		if (!arg && nodes[j].type == 0)
			return (NULL);
		free(arg);
		// if (nodes[j].args[0])
			// printf("@ word = %s, args = %s, type = %d\n",words[i], nodes[j].args[0], nodes[j].type);
		j++;
	}
	return (nodes);
}
