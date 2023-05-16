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
		return (free_struct_array(NULL, lex, nodes, len));
	while (++i < len)
	{
		nodes[i].type = 0;
		nodes[i].arg = NULL;
		nodes[i].redir = -1;
	}
	return (nodes);
}

int	nodes_count(char **word)
{
	int	i;
	int	part;

	i = -1;
	part = 0;
	while (word[++i])
	{
		// printf("'%s' ", word[i]);
		if (word[i][0] != '>' && word[i][0] != '<')
			part++;
	}
	// printf("\npart=%d\n", part);
	return (part);
}

t_token	*fill_nodes(char **words, t_lexic *lex, t_token *nodes,  int *len)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	k = 0;
	if(!nodes)
		*len = -1;
	while (words[++i] && nodes)
	{
		nodes[j].arg = cmd_split(words[i], &nodes[j].type, *lex,
				(j > 0) * nodes[j - 1].type);
		// ft_printf("i=%d j =%d k=%d token=%d\n", i, j, k, nodes[j].type);
		if (!nodes[i].arg && nodes[j].type == 0)
			return (free_struct_array(words, lex, nodes, *len));//127
		if (nodes[j].type > 21)
			nodes[k].arg = ft_strjoin(nodes[k].arg, words[(i++) + 1]);
		if (nodes[j].type == 21)
			k = i;
		j++;
	}
	return (nodes);
}
