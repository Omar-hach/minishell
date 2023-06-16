/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:41:38 by yhachami          #+#    #+#             */
/*   Updated: 2023/06/16 18:41:43 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_symb_len(int sym_type, char *s, char **sym)
{
	int	queot;
	int	double_qu;
	int	count;

	queot = 0;
	double_qu = 0;
	count = 0;
	if (sym_type < 2)
		return (1);
	else if (sym_type == 2 || sym_type == 4)
		count = 2 + count_space(s + 2);
	else if (sym_type == 3 || sym_type == 5)
		count = 1 + count_space(s + 1);
	while ((!ft_find(s + count, sym) && (s[count] != ' ' && s[count] != '\t')
			&& s[count]) || (((queot % 2) || (double_qu % 2)) && s[count]))
	{
		queot += (*(s + count) == 34) * !(double_qu % 2);
		double_qu += (*(s + count) == 39) * !(queot % 2);
		count++;
	}
	return (count);
}

int	get_token_len(char *s, char **sym)
{
	int	queot;
	int	double_qu;
	int	count;

	queot = 0;
	double_qu = 0;
	count = 0;
	while (*(s))
	{
		queot += (*s == 34) * !(double_qu % 2);
		double_qu += (*s == 39) * !(queot % 2);
		if (ft_find(s, sym) && !(queot % 2) && !(double_qu % 2))
			break ;
		count++;
		s++;
	}
	return (count);
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
	while (word[i])
		arg[j++] = word[i++];
	arg[j] = '\0';
	return (arg);
}

char	*set_arg_type(char *word, int *token, char *cmd, t_lexic lex)
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
