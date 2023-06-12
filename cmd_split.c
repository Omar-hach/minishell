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

char	*fill_cmd(char *word, int j, int *i)
{
	char	*cmd;
	int		k;

	while ((((word[(*i)] != ' ' && word[(*i)] != '\t'))
			|| !is_outside_quoet(word, *i)) && word[(*i)])
		(*i)++;
	cmd = (char *)ft_calloc((*i) + 1, sizeof(char));
	if (!cmd)
		return (NULL);
	k = -1;
	while (++k < (*i))
	{
		while (word[k] == 34 || word[k] == 39)
			k++;
		if (k < (*i))
			cmd[j++] = ft_tolower(word[k]);
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
	i = 0;
	while (j <  word[i])
		arg[j++] = word[i++];
	arg[j] = '\0';
	return (arg);
}
	// ft_memcpy(&arg[j], word, ft_strlen(word) + 1);
	// ft_printf("path=%s.  %s\n",  arg, cmd);

	// ft_printf(" ,cmd=%s , %p. word=%s , %p\n", cmd, cmd, word , word);
char	*set_cmd(char *word, int *token, char *cmd, t_lexic lex)
{
	char	*arg;
	char	*bin;

	arg = NULL;
	// if (ft_strncmp(cmd, "..", 2))
		bin = find_path(cmd);
	if (ft_find(cmd, lex.l_cmd)
		&& ft_strlen(lex.l_cmd[ft_find(cmd, lex.l_cmd) - 1]) == ft_strlen(cmd))
		*token = ft_find(cmd, lex.l_cmd) + 10;
	else if (ft_strchr(cmd, '/'))
	{
		*token = 1;
		arg = (char *)ft_calloc(ft_strlen(word) + 1, sizeof(char));
		ft_memcpy(arg, word, ft_strlen(word) + 1);
	}
	else if (bin)
	{
		*token = 1;	
		arg = expand_cmd(cmd, bin, word);
	}
	// if (bin)
		free(bin);
	return (arg);
}

//handle arg to **arg with no ""
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

//echo "hello    ">a   b   c --> cat a : helo b c
char	*cmd_split(char *word, int *token, t_lexic lex)
{
	int		i;
	int		j;
	char	*word_copy;
	char	*cmd;
	char	*arg;

	i = 0;
	j = 0;
	cmd = NULL;
	if (word && ft_find(word, lex.l_symb) != 2)
		word_copy = replace_dollars(word);
	if (ft_find(word, lex.l_symb))
		cmd = fill_symb(word_copy, &i, token, ft_find(word_copy, lex.l_symb));
	else
		cmd = fill_cmd(word_copy, j, &i);
	if (!cmd || *token == 21)
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
	// printf("-word[%p]=%s -word_copy[%p]=%s\n",word, word, word_copy, word_copy);
	free(cmd);
	free(word_copy);
	return (arg);
}
