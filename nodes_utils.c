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
	// ft_printf("--------------------\n");
	while (words[++i] && nodes)
	{
		// ft_printf("+word[0]=%p\n",words[i]);
		nodes[j].arg = cmd_split(words[i], &nodes[j].type, *lex);
		if (!nodes[i].arg && nodes[j].type == 0)
		{
			*error = 127;
			return (free_struct_array(words, lex, nodes, *len));
		}
		// ft_printf("-word[%s]=%p\n",words[i], words[i] );
		// ft_printf("i=%d j =%d k=%d token=%d cmd=%s\n", i, j, k, nodes[j].type , nodes[j].arg);
		j++;
		
	}
	// ft_printf("--------------------\n");
	return (nodes);
}
