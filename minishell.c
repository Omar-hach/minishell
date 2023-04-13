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
	lex->l_cmd[0] = "cd";
	lex->l_cmd[1] = "echo";
	lex->l_cmd[2] = "echo -n";
	lex->l_cmd[3] = "pwd";
	lex->l_cmd[4] = "export";
	lex->l_cmd[5] = "unset";
	lex->l_cmd[6] = "env";
	lex->l_cmd[7] = "exit";
	lex->l_symb = (char **)malloc(6 * sizeof(char *));
	lex->l_symb[0] = "|";
	lex->l_symb[1] = ">";
	lex->l_symb[2] = ">>";
	lex->l_symb[3] = "<";
	lex->l_symb[4] = "<<";
	lex->l_symb[5] = "$";
}
enum e_symbol :char {
	pipe = 'l',
	out = 'o',
	Out_double = 'O',
	in = 'i',
	int_double = 'I'.
	var = '$'
};
int	cmd_in_word(char **cmd, int len, char *word)
{
	int	i;
	int	j;

	j = -1;
	while(++j < len)
	{
		i = -1;
		while (word[++i])
		{
			if(cmd[i] == word[i])
				i++;
			if(cmd[i] == word[i])
				i++;
		}
	}
}

int	token_in_word(char **symb, char *word)
{

}

void	lexer_words(char **words, int num_words)
{
	s_lexic lex;
	int i;
	int j;

	creat_lexic(&lex);
	i = 0;
	j = 0;
	while (i < num_words)
	{
		if(cmd_in_word(lex.l_cmd, num_words, words[i]))
			printf("<cmd>");
		else if(ft_strlen(words[i]) < 3 && token_in_word(lex.l_symb, words[i]))
			printf("<sym>");
		else
			printf("ERROR");
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
	char **l_cmd;
	char **l_symb;

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