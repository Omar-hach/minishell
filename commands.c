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

int	ft_env(void)
{
	int			x;
	extern char	**environ;

	x = -1;
	while (environ[++x])
		printf("%s\n", environ[x]);
	return (0);
}

int	ft_unset(int ac, char **av)
{
	extern char	**environ;
	int			x;
	int			r;

	if (ac == 0)
		return (0);
	else
	{
		x = -1;
		while (av[++x])
		{
			r = is_var(av[x]);
			if (r == -1 || r == 1 || r == 0)
				return (ft_printf("unset: '%s': not a valid identifier\n",
						av[x]), 1);
			if (r == -3)
				return (ft_printf("unset: '%s': not a valid identifier\n",
						av[x]), 2);
			else
				ft_unsetenv(av[x]);
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
		ft_env_declare();
	else
	{
		x = -1;
		while (av[++x])
		{
			r = is_var(av[x]);
			if (r == -1 || r == -2 || r == 0)
				return (ft_printf("export: '%s': not a valid identifier\n",
						av[x]), 1);
			else if (r == -3 || r == -4)
				return (ft_printf("export: '%s': not a valid identifier\n",
						av[x]), 2);
			else if (r == 3 || r == 2)
				return (0);
			else
				ft_setenv(ft_strdup(av[x]));
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
		if (x == 0 && av[0][0] != '0')
		{
			ft_printf("exit: %s: numeric argument required\n", av[0]);
			exit(255);
		}
	}
	if (ac == 0)
		exit(0);
	if (ac == 1)
	{
		x = (char) ft_atoi(av[0]);
		if (x == 0 && av[0][0] != '0')
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

	ac = 0;
	while (token.args[ac])
		ac++;
	out = -1;
	if (token.type == 11)
		out = ft_env();
	else if (token.type == 12)
		out = ft_pwd();
	else if (token.type == 13)
		out = ft_cd(ac, token.args);
	else if (token.type == 15)
		out = ft_export(ac, token.args);
	else if (token.type == 16)
		out = ft_unset(ac, token.args);
	else if (token.type == 17)
		out = ft_echo(ac, token.args);
	else if (token.type == 14)
		out = ft_exit(ac, token.args);
	return (out);
}
