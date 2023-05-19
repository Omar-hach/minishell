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

int	ft_env(int exp)
{
	int			x;
	int			y;
	int			z;
	extern char	**environ;

	x = -1;
	while (environ[++x])
	{
		if (exp)
		{
			printf("declare -x ");
			y = -1;
			z = 0;
			while (environ[x][++y])
			{
				printf("%c", environ[x][y]);
				if (environ[x][y] == '=')
				{
					printf("\"");
					z++;
				}
			}
			if (z)
				printf("\"");
			printf("\n");
		}
		else
			printf("%s\n", environ[x]);
	}
	return (0);
}

int	ft_unset(int ac, char **av)
{
	extern char	**environ;
	int			x;
	int			y;
	int			r;

	if (ac == 0)
	{
		// perror("unset: not enough arguments");
		return (0);
	}
	else
	{
		x = -1;
		while (av[++x])
		{
			y = 0;
			while (av[x][++y])
			{
				if (av[x][y] == '=')
				{
					ft_printf("unset: '%s': not a valid identifier\n", av[x]);
					return (1);
				}
				if (av[x][y] == ';')
				{
					ft_printf("unset: '%s': not a valid identifier\n", av[x]);
					return (127);
				}
			}
			r = ft_isvar(av[x]);
			if (av[x][0] == '-')
			{
				ft_printf("unset: '%s': not a valid identifier\n", av[x]);
				return (2);
			}
			if (r == 0 || r == -1)
			{
				ft_printf("unset: '%s': not a valid identifier\n", av[x]);
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
	int			r;

	if (ac == 0)
		ft_env(1);
	else
	{
		x = -1;
		while (av[++x])
		{
			r = ft_isvar(av[x]);
			if (av[x][0] == '-')
			{
				ft_printf("export: '%s':  not a valid identifier\n", av[x]);
				return (2);
			}
			if ((av[x][0] >= '0' && av[x][0] <= '9') || r == 0 || r == -1)
			{
				ft_printf("export: '%s':  not a valid identifier\n", av[x]);
				return (1);
			}
			if (r == -3 || r == -2)
				return (0);
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
	char	x;

	if (av[0])
	{
		x = (char) ft_atoi(av[0]);
		if (x == 0 && av[0][0] != '0' && av[0][1] != '0')
		{
			ft_printf("exit: %s: numeric argument required\n", av[0]);
			exit(255);
		}
	}
	if (ac == 1)
	{
		x = (char) ft_atoi(av[0]);
		if (x == 0 && av[0][1] != '0' && av[0][0] != '0')
			exit(255);
		exit(x);
	}
	else if (ac > 1)
	{
		ft_printf("exit: too many arguments\n");
		return (1);
	}
	return (0);
}

int	exec_cmd(t_token token)
{
	int		out;
	int		ac;
	char	**av;

	av = token.args;
	ac  = 0;
	while (av[ac])
		ac++;
	out = -1;
	if (token.type == 11)
		out = ft_env(0);
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
