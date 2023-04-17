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
#include"minishell.h"

int ex;

void creat_lexic(s_lexic *lex)
{
	lex->l_cmd = (char **)malloc(8 * sizeof(char *));
	if(!lex->l_cmd)
		exit(1);
	lex->l_cmd[0] = "env";
	lex->l_cmd[1] = "pwd";
	lex->l_cmd[2] = "cd";
	lex->l_cmd[3] = "exit";
	lex->l_cmd[4] = "export";
	lex->l_cmd[5] = "unset";
	lex->l_cmd[6] = "echo";
	lex->l_symb = (char **)malloc(6 * sizeof(char *));
	if(!lex->l_cmd)
	{
		free(lex->l_cmd);
		exit(1);
	}
	lex->l_symb[0] = "|";
	lex->l_symb[1] = ">";
	lex->l_symb[2] = ">>";
	lex->l_symb[3] = "<";
	lex->l_symb[4] = "<<";
	lex->l_symb[5] = "$";
}
/*
enum e_symbol :char {
	pipe = 'l',
	out = 'o',
	Out_double = 'O',
	in = 'i',
	int_double = 'I'.
	var = '$'
};*/


int	token_in_word(char **token, int len, char *word, int type)
{
	int	i;
	int	j;
	int	diff;

	j = -1;
	i = -1;
	diff = 1;
	while(++j < len)
	{
		i = -1;
		while (token[++i] && diff)
			diff = ft_strncmp(token[i], word, ft_strlen(token[i]));
		if(!diff)
			return(i + 1 + 10 * type);
	}
	return(10 * type);
}

int detect_arg(int *cmd_type)
{
	if (*cmd_type / 10 != 2)
		return (0);
	if (*cmd_type % 10 > 1)
		return (1);
	if (*cmd_type % 10 > 3)
		return (30);
	if (*cmd_type % 10 > 5)
		return (50/*join arg*/);
	return (9);
}

void	lexer_words(char **words, int num_words)
{
	s_lexic	lex;
	int	i;
	int	*class;
	//int error;

	creat_lexic(&lex);
	//error = 0;
	i = 0;
	class = (int *) ft_calloc(num_words, sizeof(int));
	while (++i < num_words)
	{
		class[i] = token_in_word(lex.l_cmd, num_words, words[i], 2);
		if(!(class[i] % 10))
			class[i] = token_in_word(lex.l_symb, num_words, words[i], 1);
		if (!(class[i] % 10) && i > 0)
			class[i] = detect_arg(&class[i - 1]);
		printf("<%d>",class[i]);
	}
	printf("\n");
}

void	split_input(char *input)
{
	int i;
	int count;
	char **words;

	i = 0;
	count = 0;
	while (input[++i])
	{
		if((input[i] == ' ' && input[i - 1] != ' ')
		|| (input[i + 1] == '\0' && input[i] != ' '))
			count++;
	}
	words = ft_split(input, ' ');
	lexer_words(words, count);
}
//<cmd><|><exp>
int	main()
{
	char* input;
	//char **l_cmd;
	//char **l_symb;

	while(!ex)
	{
		input = readline(">>> MiniShell $>");
		if(*input)
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
