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

int	ft_env(char **env)
{
	int			x;

	x = -1;
	while (env[++x])
		printf("%s\n", env[x]);
	return (0);
}

int	ft_unset(int ac, char **av, char **env)
{
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
				ft_unsetenv(env, av[x]);
		}
	}
	return (0);
}

int	ft_export(int ac, char **av, char **env)
{
	int			x;
	int			r;

	if (ac == 0)
		ft_env_declare(env);
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
				ft_setenv(env, ft_strdup(av[x]));
		}
	}
	return (0);
}

int	ft_exit(int ac, char **av, t_tree *tree, t_token *tokens)
{
	char	x;

	exit_check_num(av[0], tree, tokens);
	if (ac == 0)
		exit_outside(0, tree, tokens);
	else if (ac == 1)
	{
		x = (char) ft_atoi(av[0]);
		if (x == 0 && av[0][0] != '0' && av[0][1] != '0')
			exit_outside(255, tree, tokens);
		exit_outside(x, tree, tokens);
	}
	else if (ac > 1)
	{
		ft_printf("exit: too many arguments\n");
		return (1);
	}
	return (0);
}

int	exec_cmd(t_tree *tree, t_token *tokens, int x, char **env)
{
	int		out;
	int		ac;

	ac = 0;
	while (tokens[x].args[ac])
		ac++;
	out = -1;
	if (tokens[x].type == 11)
		out = ft_env(env);
	else if (tokens[x].type == 12)
		out = ft_pwd();
	else if (tokens[x].type == 13)
		out = ft_cd(ac, tokens[x].args, env);
	else if (tokens[x].type == 15)
		out = ft_export(ac, tokens[x].args, env);
	else if (tokens[x].type == 16)
		out = ft_unset(ac, tokens[x].args, env);
	else if (tokens[x].type == 17)
		out = ft_echo(ac, tokens[x].args);
	else if (tokens[x].type == 14)
		out = ft_exit(ac, tokens[x].args, tree, tokens);
	return (out);
}
