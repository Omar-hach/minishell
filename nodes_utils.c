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
		nodes[i].in = 0;
		nodes[i].out = 1;
		// nodes[i].redir = (int *) malloc(2 * sizeof(int));
		// if (pipe(nodes[i].redir) < 0)
		// {
			// free(nodes[i].redir);
			// nodes[i].redir = NULL;
		// }
		nodes[i].qt = -1;
	}
	return (nodes);
}

int	nodes_count(char **word)
{
	int	i;
//	int	part;

	i = 0;
	while (word[i])
	{
		//printf("'%s' ", word[i]);
		i++;
	}
	//printf("\npart=%d\n", i);
	return (i);
}

t_token	*fill_nodes(char **words, t_lexic *lex, t_token *nodes,  int *len)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	if (!nodes)
		*len = -1;
	while (words[++i] && nodes)
	{
		//printf("*word[%p]=%s=%p, i=%d\n",words, words[i], words[i], i);
		nodes[j].arg = cmd_split(words[i], &nodes[j].type, *lex);
		//printf("*word[%p]=%s=%p, i=%d\n",words, words[i], words[i], i);
		if (!nodes[i].arg && nodes[j].type == 0)
			return (NULL);
		// printf("\n[%d] word = %s, arg = %s , type = %d\n", i, words[i], nodes[j].arg, nodes[j].type);
		j++;
	}
	free(words);
	return (nodes);
}
