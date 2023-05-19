/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 23:54:42 by ohachami          #+#    #+#             */
/*   Updated: 2023/05/15 23:54:45 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

char	**trim_word(char *words, int type)
{
//	char	**arg;
	int		len = 0;
//	int		i = -1;
	int		queot = 0;
	int		double_qu = 0;
	char	*sepr;

	sepr = ft_strdup(" 	");
    words += count_space(words);
	while (*words)
	{
		queot += (*words == 34) * !(double_qu % 2);
		double_qu += (*words == 34) * !(queot % 2);
        printf("words =%s quo = %d qu = %d\n", words, queot, double_qu);
		if ((*words != ' ' && *words != '\t' && *words != '\0') 
			&& (*(words + 1) == ' ' || *(words + 1) == '\t' || *(words + 1) == '\0')
			&& !(queot % 2) && !(double_qu % 2))
		{
			// printf("-->words =%s\n", words);
			len++;
		}
		words += count_space(words);
        words++;
	}
	printf("len =%d type =%d\n", len, type);
	(void)(type);
	return(NULL);
}
/*
int main()
{
	char	*word;
	word = ft_strdup("echo 'hah' " " 'jojo' df" "good 	 kd " 	" l");
	trim_word(word, 1);
}*/