/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
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
		free(words[i]);
	free(words);
	return (NULL);
}

void	*free_struct_array(char **words, t_lexic *lex, t_token *nodes, int len)
{
	int	i;

	i = -1;
	while (nodes && ++i < len)
	{
		ft_printf("arg=%p, len=%d\n", nodes[i].arg, len);
		if (nodes[i].arg)
			free(nodes[i].arg);
	}
	if (nodes)
		free(nodes);
	if (words)
		free_aray(words);
	if (lex && lex->l_cmd)
		free_aray(lex->l_cmd);
	if (lex && lex->l_symb)
		free_aray(lex->l_symb);
	return (NULL);
}