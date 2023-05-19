/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 20:22:42 by yhachami          #+#    #+#             */
/*   Updated: 2023/05/13 20:22:44 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	get_single_flag(char *s)
{
	char	f;
	int		y;

	y = 0;
	f = '0';
	if (s[0] == '-')
	{
		while (s[++y])
		{
			if (s[y] == 'n')
				f = 'n';
			else
			{
				f = '0';
				break;
			}
		}
	}
	return (f);
}

char	get_flag(char **s, int *x)
{
	char	f;
	char	flag;

	flag = '0';
	while (s[++*x])
	{
		f = get_single_flag(s[*x]);
		if (f == 'n')
			flag = 'n';
		else if (f == '0')
		{
			*x -= 1;
			break ;
		}
	}
	return (flag);
}

int	ft_echo(int ac, char **av)
{
	// char	*txt;
	char	flag;
	int		x;
	int		start;

	if (ac > 0)
	{
		x = -1;
		flag = get_flag(av, &x);
		start = 1;
		// ft_printf("%s = %c\n",av[x] , flag);
		while (++x < ac)
		{
			if (start == 0)
				printf(" ");
			start = 0;
			// av[x] = extra_cd(av[x]); 
			if (flag == 'n')
				printf("%s",av[x]);
			else if (flag == '0')
				printf("%s",av[x]);
			// free(txt);
		}
	}
	if (ac == 0 || flag == '0')
		printf("\n");
	return (0);
}
