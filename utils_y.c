/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_y.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 15:47:04 by yhachami          #+#    #+#             */
/*   Updated: 2023/04/28 15:47:07 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// AAAMMMBBIIGGUUUS
int	ambiguous(char *word, char *word_copy, int type, int *token)
{
	if (!word_copy || *token == 21)
		return (0);
	if (word_copy && (type == 1 || type == 3) && !word_copy[1])
	{
		*g_error = 127;
		ft_printf("minshell: %s: ambiguous redirect\n", word + 1);
		return (0);
	}
	if (word_copy && (type == 2 || type == 4) && !word_copy[2])
	{
		*g_error = 127;
		ft_printf("minshell: %s: ambiguous redirect\n", word + 2);
		return (0);
	}
	return (1);
}

// check if exit command has numbre argument
void	exit_check_num(char *av, t_tree *tree, t_token *tokens)
{
	int	x;

	if (av)
	{
		x = (char) ft_atoi(av);
		if (x == 0 && av[0] != '0' && av[1] != '0')
		{
			ft_printf("exit: %s: numeric argument required\n", av);
			exit_outside(255, tree, tokens);
		}
	}
}

// get the VAR name in $VAR
char	*get_dollar_name(char *s, int x, int z)
{
	int		y;
	char	*name;

	name = (char *) malloc ((z + 1) * sizeof(char));
	if (!name)
		return (NULL);
	y = x;
	z = 0;
	while (s[++y] && is_money_end(s[y]))
	{
		name[z++] = s[y];
		if (y == x + 1 && ft_isdigit(s[y]))
			break ;
	}
	name[z] = '\0';
	return (name);
}

// error check for fork
int	fork1(void)
{
	int	pid;

	pid = fork();
	if (pid < 0)
	{
		ft_printf("couldnt fork\n");
		return (-1);
	}
	return (pid);
}

// error check for dup2
int	ft_dup(int fd, int fd2replace)
{
	if (dup2(fd, fd2replace) < 0)
	{
		ft_printf("%d, couldnt redirect to fd %d\n", fd, fd2replace);
		return (-1);
	}
	return (0);
}
