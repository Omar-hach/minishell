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
	// char		*out;

	// x = -1;
	// while (environ[++x])
	// 	out = join_args(environ, '\n');
	// ft_printf(out);
	x = -1;
	while (environ[++x])
		ft_printf("%s\n", environ[x]);
	return (0);
}

int	ft_echo(char *arg, char flag)
{
	// char	*out;

	// if (flag == 'n')
	// 	out = ft_strdup(arg);
	// else if (flag == 0)
	// 	out = ft_strdup_newline(arg);
	// ft_printf(out);
	if (dola_dola(arg))
	{
		ft_printf(dola_dola(arg));
		ft_printf("\n");
	}
	else if (flag == 'n')
		ft_printf(arg);
	else if (flag == 0)
	{
		ft_printf(arg);
		ft_printf("\n");
	}
	return (0);
}

int	ft_pwd()
{
	char	*dir;
	int		i;

	dir = (char *)malloc(PATH_MAX);
	getcwd(dir, PATH_MAX);
	i = 0;
	while (dir[i])
		i++;
	//out = (char *)malloc((i + 2) * sizeof(char));
	//i = -1;
	//while (dir[++i] != '\0')
	//	out[i] = dir[i];
	dir[i++] = '\n';
	dir[i] = '\0';
	ft_printf(dir);
	free(dir);
	return (0);
}

int	ft_cd(char *arg)
{
	DIR	*dir;

	dir = opendir(arg);
	if (dir)
	{
		if (chdir(arg) < 0)
		{
			perror("cannot change dir");
			return (1);
		}
	}
	else
	{
		perror("dir don exist");
		return (2);
	}
	return (0);
}

int	ft_unset(char *arg)
{
	extern char	**environ;
	char		**args;
	int			x;

	args = ft_split(arg, ' ');
	x = -1;
	while (args[++x])
	{
		if (ft_findvar(args[x]) == -1)
		{
			perror("not a valid variable");
			return (1);
		}
		else
			ft_unputenv(args[x]);
	}
	return (0);
}

int	ft_export(char *arg)
{
	extern char	**environ;
	char		**args;
	int			x;

	args = ft_split(arg, ' ');
	x = -1;
	while (args[++x])
	{
		if (ft_isvar(args[x]) == 0)
		{
			perror("not a valid variable");
			return (1);
		}
	}
	x = -1;
	while (args[++x])
	{
		ft_putenv(args[x]);
		// ft_printf("export = %s\n",getenv(args[x]));
	}
	// ft_env();
	// ft_unset("VR ok");
	// ft_env();
	return (0);
}

int	ft_exit()
{
	return (0);
}

int	exec_cmd(t_token token)
{
	int	out;

	out = 0;
	if (token.type == 11)
		out = ft_env();
	else if (token.type == 12)
		out = ft_pwd();
	else if (token.type == 13)
		out = ft_cd(token.arg);
	else if (token.type == 15)
		out = ft_export(token.arg);
	else if (token.type == 16)
		out = ft_unset(token.arg);
	else if (token.type == 17)
		out = ft_echo(token.arg, 0);
	return (out);
}
