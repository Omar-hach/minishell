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
			|| !is_outside_quoet(word, *i)) && word[(*i)])
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

char	*expand_cmd(char *cmd, char *bin, char *word)
{
	int		i;
	int		j;
	char	*arg;

	arg = (char *)ft_calloc(ft_strlen(bin) + ft_strlen(word) + 1, sizeof(char));
	i = ft_strlen(bin) - ft_strlen(cmd);
	j = -1;
	while (++j < i)
		arg[j] = bin[j];
	i = count_space(word);
	while (j < word[i])
		arg[j++] = word[i++];
	arg[j] = '\0';
	return (arg);
}

char	*set_cmd(char *word, int *token, char *cmd, t_lexic lex)
{
	char	*arg;
	char	*bin;

	arg = NULL;
	if (ft_find(cmd, lex.l_cmd)
		&& ft_strlen(lex.l_cmd[ft_find(cmd, lex.l_cmd) - 1]) == ft_strlen(cmd))
		*token = ft_find(cmd, lex.l_cmd) + 10;
	else if (ft_strchr(cmd, '/'))
	{
		*token = 1;
		arg = (char *)ft_calloc(ft_strlen(word) + 1, sizeof(char));
		ft_memcpy(arg, word, ft_strlen(word) + 1);
	}
	else
	{
		bin = find_path(cmd);
		if (bin)
		{
			*token = 1;
			arg = expand_cmd(cmd, bin, word);
		}
		free(bin);
	}
	return (arg);
}

char	*fill_arg(char *word, int i)
{
	char	*arg;
	int		shift;

	arg = (char *)ft_calloc(ft_strlen(word + i) - count_space(word + i) + 1,
			sizeof(char));
	if (!arg)
		return (NULL);
	shift = count_space(word + i) + i;
	word += shift;
	i = -1;
	while (word[++i])
		arg[i] = word[i];
	arg[i] = '\0';
	word -= shift;
	return (arg);
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

char	*cmd_def(char *word_copy, int *i, int *token, t_lexic lex)
{
	char	*cmd;

	cmd = NULL;
	if (ft_find(word_copy, lex.l_symb))
		cmd = fill_symb(word_copy, i, token, ft_find(word_copy, lex.l_symb));
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
	cmd = cmd_def(word_copy, &i, token, lex);
	if (!word_copy || !cmd || *token == 21)
	{
		free(cmd);
		free(word_copy);
		return (NULL);
	}
	arg = set_cmd(word_copy, token, cmd, lex);
	if (*token < 1)
	{
		*g_error = 127;
		ft_printf("minshell: %s: command not found\n", cmd);
	}
	if (!arg && *token > 1)
		arg = fill_arg(word_copy, i);
	free(cmd);
	free(word_copy);
	return (arg);
}

// ft_h(char *word_copy, char *cmd, int *token, int len)
// {
// 	char	*arg;

// 	*arg = NULL;
// 	if (!word_copy || !cmd || *token == 21)
// 	{
// 		free(cmd);
// 		free(word_copy);
// 		return (NULL);
// 	}
// 	arg = set_cmd(word_copy, token, cmd, lex);
// 	if (*token < 1)
// 	{
// 		*g_error = 127;
// 		ft_printf("minshell: %s: command not found\n", cmd);
// 	}
// 	if (!arg && *token > 1)
// 		arg = fill_arg(word_copy + count_space(word_copy), len);
// 	return(arg);
// }

// //echo "hello    ">a   b   c --> cat a : helo b c
// char	*cmd_split(char *word, int *token, t_lexic lex)
// {
// 	int		len;
// 	char	*word_copy;
// 	char	*cmd;
// 	char	*arg;

// 	len = 0;
// 	cmd = NULL;
// 	word_copy = NULL;
// 	if (word && ft_find(word, lex.l_symb) == 2)
// 		word_copy = ft_strdup(word);
// 	else if (word && *token != 21)
// 		word_copy = replace_dollars(word);
// 	if (ft_find(word_copy, lex.l_symb))
// 		cmd = fill_symb(word_copy, &len, token, ft_find(word_copy, lex.l_symb));
// 	else
// 		cmd = fill_cmd(word_copy, &len);
// 	arg = ft(word_copy, cmd, token, len);
// 	free(cmd);
// 	free(word_copy);
// 	return (arg);
// }