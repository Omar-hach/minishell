/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:14:18 by ohachami          #+#    #+#             */
/*   Updated: 2023/03/26 23:14:59 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

int ex;

void creat_lexic(s_lexic *lex)
{
	lex->l_cmd = (char **)malloc(8 * sizeof(char *));
	if (!lex->l_cmd)
		exit(1);
	lex->l_cmd[0] = "env";
	lex->l_cmd[1] = "pwd";
	lex->l_cmd[2] = "cd";
	lex->l_cmd[3] = "exit";
	lex->l_cmd[4] = "export";
	lex->l_cmd[5] = "unset";
	lex->l_cmd[6] = "echo";
	lex->l_cmd[6] = NULL;
	lex->l_symb = (char **)malloc(6 * sizeof(char *));
	if (!lex->l_cmd)
	{
		free(lex->l_cmd);
		exit(1);
	}
	lex->l_symb[0] = "|";
	lex->l_symb[1] = ">>";
	lex->l_symb[2] = ">";
	lex->l_symb[3] = "<<";
	lex->l_symb[4] = "<";
	lex->l_symb[5] = NULL;
}
/*
void	exp_cont(char *input)
{
	int i;
	int part = 1;
	int len;
	int indix;
	char *sub;

	i = -1;
	len = -1;
	indix = 0;
	sub = NULL;
	while (input[++i])
	{
		if ((input[i + 1] == '|' || input[i + 1] == '>' || input[i + 1] == '>')
			&& input[i] == ' ' && input[i + 2] == ' ')
			part++;
		if( () || (input[i] == ' ')
			&& input[i] == ' ' &&input[i + 3] == ' ')
		while(input[++len])
		{
			if((input[len] != ' '  || input[len] != '\t') && input[len + 1]
				&& (input[len + 1] == ' '  || input[len + 1] == '\t'))
				break;
		}
		if (!i)
		{
			sub = ft_substr(input,i,len);
			indix = token_in_word(lex, sub);
			free(sub);
			if(indix / 2)
				part++;
		}
		i += len -1;
	}
}

*/
// Error handler
int count_space(char *s)
{
	int i;

	i = 0;
	while (s[i] && ((s[i] == ' ') || (s[i] == '\t')))
		i++;
	return (i);
}

int ft_find(char *s, char **sym)
{
	int i;
	int diff;

	i = -1;
	diff = 0;
	while (sym[++i])
	{
		diff = ft_strncmp(sym[i], s, ft_strlen(sym[i]));
		if (!diff)
			return (i + 1);
	}
	return (0);
}

int error_print(char *mes, char *prob, int n)
{
	printf("%s '", mes);
	while (n--)
	{
		printf("%c", *prob);
		prob++;
	}
	printf("'\n");
	return (1);
}

int last_char(char *s, int queot, int double_qu)
{
	while (*s == ' ' || *s == '\t')
		s--;
	if (*s == '>' || *s == '|' || *s == '$' || *s == '<')
	{
		printf("minshell: syntax error near unexpected token `%c'\n", *s);
		return (1);
	}
	if (queot % 2)
	{
		printf("minshell: syntax error near unexpected token %c\n", (queot % 2) * 34);
		return (1);
	}
	if (double_qu % 2)
	{
		printf("minshell: syntax error near unexpected token %c\n", (double_qu % 2) * 39);
		return (1);
	}
	return (0);
}

int detect_sym_error(char *s, char **sym, int *part)
{
	int queot;
	int double_qu;

	queot = 0;
	double_qu = 0;
	while (*s)
	{
		queot += (*s == 34);
		double_qu += (*s == 39);
		if ((*s == ';' || *s == 92) && !(queot % 2) && !(double_qu % 2))
			return (error_print("minshell: syntax error near unexpected token", s, 1));
		s++;
		if (*s && ft_find(s, sym) && !(queot % 2) && !(double_qu % 2))
		{
			s += ft_strlen(sym[ft_find(s, sym) - 1]);
			s += count_space(s);
			if (ft_find(s, sym))
				return (error_print("minshell: syntax error near unexpected token",
									sym[ft_find(s, sym) - 1], ft_strlen(sym[ft_find(s, sym) - 1])));
			*part += 2;
		}
	}
	return (last_char(s - 1, queot, double_qu));
}

int *word_len(char *s, char **sym, int part)
{
	int *array;
	int i;
	int queot;
	int double_qu;

	array = (int *)malloc(part * sizeof(int));
	if (!array)
		return (NULL);
	i = 0;
	queot = 0;
	double_qu = 0;
	while (*s)
	{
		array[i] = 0;
		queot += (*s == 34);
		double_qu += (*s == 39);
		while (*(++s) && (!ft_find(s, sym) || (!(queot % 2) && !(double_qu % 2))))
			array[i]++;
		if (ft_find(s, sym) && ((queot % 2) || (double_qu % 2)))
			array[i++] = ft_strlen(sym[ft_find(s, sym)]);
		printf("s=%s\n", s);
		ft_printf("array[%d]=%d\n", i, array[i]);
		if (!*s || i >= part - 1)
			break;
		i++;
	}
	return (array);
}
/*
char	**word_cutter(char *s, char **sym, char **array)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (s[k])
	{
		if (!ft_find(&s[k],sym))
		{
			array[i][j] = s[k];
			j++;
			if (ft_find(&s[k + 1],sym))
			{
				i++;
				j = 0;
			}
		}
		k++;
	}
	return (array);
}
*/
char **expr_split(char *s, char **sym)
{
	char **array;
	//	int		i;
	int *len_array;
	int part;

	array = NULL;
	part = 1;
	if (detect_sym_error(s, sym, &part))
		return (NULL);
	printf("part : %d\n", part);
	array = (char **)malloc((part) * sizeof(char *));
	if (!array)
		return (NULL);
	len_array = word_len(s, sym, part);
	if (len_array)
	{
		free(array);
		return (NULL);
	}
	/*i = -1;
	while (++i < part)
		array[i] = (char *)ft_calloc(len_array[i], sizeof(char));
	array = word_cutter((char *)s, sym, array);
	array[i] = NULL;*/
	free(len_array);
	return (array);
}

void split_input(char *input)
{
	int i;
	s_lexic lex;
	char **words;

	creat_lexic(&lex);
	words = expr_split(input, lex.l_symb);
	i = -1;
	while (words && words[++i])
		printf("<%s>", words[i]);
	// printf("\n");
	free(lex.l_cmd);
	free(lex.l_symb);
}
//<cmd><|><exp>
int main()
{
	char *input;
	// char **l_cmd;
	// char **l_symb;

	while (!ex)
	{
		input = readline(">>> MiniShell $>");
		if (*(input + count_space(input)))
		{
			add_history(input);
			split_input(input);
		}
		free(input);
	}
	exit(0);
}
//"e""c""h""o" hello need to work
// error file name too long.
