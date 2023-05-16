/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 17:39:32 by yhachami          #+#    #+#             */
/*   Updated: 2023/04/24 17:39:36 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int	ft_env()
{
	int			x;
	extern char	**environ;

	x = -1;
	while (environ[++x])
		ft_printf("%s\n", environ[x]);
	return (0);
}

int	ft_unset(int ac, char **av)
{
	extern char	**environ;
	int			x;

	if (ac == 0)
	{
		perror("unset: not enough arguments");
		return (1);
	}
	else
	{
		x = -1;
		while (av[++x])
		{
			if (ft_isvar(av[x]) == 0)
			{
				perror("unset: invalid parameter name");
				return (1);
			}
			else
				ft_unputenv(av[x]);
		}
	}
	return (0);
}

int	ft_export(int ac, char **av)
{
	extern char	**environ;
	int			x;

	if (ac == 0)
		ft_env();
	else
	{
		x = -1;
		while (av[++x])
		{
			if (ft_isvar(av[x]) == 0)
			{
				perror("export: not valid in this context");
				return (1);
			}
			else
			{
				ft_putenv(av[x]);
				// ft_printf("exported = %s\n",getenv(av[x]));
			}
		}
	}
	return (0);
}

int	ft_exit(int ac, char **av)
{
	int	x;

	if (av[0])
	{
		x = -1;
		while (av[0][++x])
		{
			if (ft_isdigit(av[0][x]) == 0)
			{
				perror("exit: numeric argument required");
				exit(0);
			}
		}
	}
	if (ac == 0)
	{
		x = ft_atoi(av[0]);
		exit(x);
	}
	else if (ac > 1)
	{
		perror("exit: too many arguments");
		return (1);
	}
	return (0);
}

int	exec_cmd(t_token token)
{
	int		out;
	int		ac;
	char	**av;

	// av = ft_split(token.arg, ' ');
	av = token.args;
	ac  = 0;
	while (av[ac])
		ac++;
	out = -1;
	if (token.type == 11)
		out = ft_env();
	else if (token.type == 12)
		out = ft_pwd();
	else if (token.type == 13)
		out = ft_cd(ac, av);
	else if (token.type == 15)
		out = ft_export(ac, av);
	else if (token.type == 16)
		out = ft_unset(ac, av);
	else if (token.type == 17)
		out = ft_echo(ac, av);
	else if (token.type == 14)
		out = ft_exit(ac, av);
	free(av);
	return (out);
}
