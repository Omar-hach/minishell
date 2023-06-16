/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 11:14:57 by ohachami          #+#    #+#             */
/*   Updated: 2023/06/11 11:15:00 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*fill_cmd(char *word, int *i)
{
	char	*cmd;
	int		k;
	int		j;

	word += count_space(word);
	while ((((word[(*i)] != ' ' && word[(*i)] != '\t'))
			|| !is_outside_quotes(word, *i)) && word[(*i)])
		(*i)++;
	cmd = (char *)ft_calloc((*i) + 1, sizeof(char));
	if (!cmd)
		return (NULL);
	k = -1;
	j = 0;
	while (++k < (*i))
	{
		while (word[k] == 34 || word[k] == 39)
			k++;
		if (k < (*i))
			cmd[j++] = word[k];
	}
	return (cmd);
}

char	*fill_symb(char *word, int *i, int *token, int type)
{
	char	*sym;
	int		j;

	(*i) = -1;
	j = 1;
	if ((word[0] == '>' && word[1] == '>')
		|| (word[0] == '<' && word[1] == '<'))
		j = 2;
	sym = (char *)ft_calloc(j + 1, sizeof(char));
	while (++(*i) < j)
		sym[(*i)] = word[(*i)];
	sym[j] = '\0';
	*token = type + 20;
	return (sym);
}

char	*word_def(char *word, int *token, t_lexic lex)
{
	char	*word_copy;

	word_copy = NULL;
	if (word && ft_find(word, lex.l_symb) == 2)
		word_copy = ft_strdup(word);
	else if (word && *token != 21)
		word_copy = replace_dollars(word);
	return (word_copy);
}

char	*cmd_def(char *word_copy, int *i, int *token, int type)
{
	char	*cmd;

	cmd = NULL;
	if (type)
		cmd = fill_symb(word_copy, i, token, type);
	else
		cmd = fill_cmd(word_copy, i);
	return (cmd);
}

char	*cmd_split(char *word, int *token, t_lexic lex)
{
	int		i;
	char	*cmd;
	char	*word_copy;
	char	*arg;

	i = 0;
	word_copy = word_def(word, token, lex);
	cmd = cmd_def(word_copy, &i, token, ft_find(word, lex.l_symb));
	if (!cmd || !ambiguous(word, word_copy, ft_find(word, lex.l_symb), token))
	{
		free(cmd);
		free(word_copy);
		return (NULL);
	}
	arg = set_arg_type(word_copy, token, cmd, lex);
	if (*token < 1)
	{
		*g_error = 127;
		ft_printf("minshell: %s: command not found\n", cmd);
	}
	if (!arg && *token > 1)
		arg = fill_arg(word_copy + count_space(word_copy), i);
	free(cmd);
	free(word_copy);
	return (arg);
}
