/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 19:38:41 by yhachami          #+#    #+#             */
/*   Updated: 2023/05/01 19:38:46 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// int	ft_findvar2(char *var)
// {
// 	int			x;
// 	int 		size;
// 	extern char	**environ;

// 	x = 0;
// 	while (environ[x])
// 	{
// 		size = 0;
// 		while (environ[x][size] != '=')
// 			size++;
// 		if (size == ft_strlen(var) && ft_strncmp(environ[x], var, size) == 0)
// 			return (x);
// 		x++;
// 	}
// 	return (-1);
// }

// void	ft_setenv(char *name)
// {
// 	int			x;
// 	extern char	**environ;

// 	x = ft_findvar(environ, name);
// 	if (x == -1)
// 		ft_putenv(name);
// 	else
// 		environ[x] = ft_strdup(name);
// }

char	*mint_dollars(char *s, int start, int name_len, char *val)
{
	int		size;
	char	*no_money;
	int 	x;
	int		y;

	// ft_printf("s=%d name=%d val=%d\n",ft_strlen(s) , name_len ,ft_strlen(val));
	size = ft_strlen(s) - name_len + ft_strlen(val) + 1;
	no_money = (char *) malloc (size * sizeof(char));
	x = -1;
	while (++x <= start)
		no_money[x] = s[x];
	// x--;
	// ft_printf("x=%d\n",x);
	y = 0;
	while (y < ft_strlen(val))
	{
		no_money[x + y] = val[y];
		y++;
	}
	y += x;
	x += name_len + 1;
	// ft_printf("x=%d\n",x);
	while (x < size)
		no_money[y++] = s[x++];
	no_money[x] = '\0';
	return (no_money);
}

char	*get_dollars(char *s, int x)
{
	int	y;
	int	z;
	char *name;
	char *val;

	while (s[x] && s[x] != '$')
		x++;
	if (x == ft_strlen(s))
		return (0);
	y = x;
	z = 0;
	while (s[x] && s[x++] != ' ')
		z++;
	if (z <= 1)
		return (0);
	name = (char *) malloc (z * sizeof(char));
	x = y;
	z = -1;
	while (s[x] && s[x] != ' ')
		name[z++] = s[x++];
	name[z] = '\0';
	val = getenv(name);
	// ft_printf("%s, start=%d len=%d name=%s ,%s\n",s , y ,z ,name, val);
	return (mint_dollars(s, y - 1 , z , val));
}

char	*dola_dola(char *s)
{
	int	x;
	char *out;

	out = s;
	x = -1;
	while (s[++x])
	{
		if (s[x] == '$')
		{
			out = get_dollars(out, x);
		}
	}
	return (out);
}

int	ft_findvar(char *var)
{
	int			x;
	int			size;
	extern char	**environ;

	x = 0;
	while (environ[x])
	{
		size = 0;
		while (var[size] && var[size] != '=')
			size++;
		if (environ[x][size] == '=' && ft_strncmp(environ[x], var, size) == 0)
			return (x);
		x++;
	}
	return (-1);
}

int	replace_var(char *name, char *value)
{
	extern char	**environ;
	int			x;
	int			y;
	int			size;
	char		*val;

	x = ft_findvar(name);
	if (x >= 0)
	{
		size = ft_strlen(name) + ft_strlen(value) + 2;
		val = (char *) malloc(size * sizeof(char));
		y = -1;
		while (++y < ft_strlen(name))
			val[y] = name[y];
		val[y] = '=';
		x = 0;
		while (++y < size)
			val[y] = value[x++];
		val[y] = '\0';
		x = ft_findvar(name);
		environ[x] = val;
		return (0);
	}
	else
		return (-1);
}

int	ft_isvar(char *var)
{
	// int	size;
	int	x;
	int	y;

	x = -1;
	while (var[++x])
	{
		if (var[x] == '=')
		{
			y = x - 1;
			while (var[y] && (ft_isalnum(var[y]) == 1 || var[y] == '_'))
			{
				y--;
				if (y == -1)
					return (1);
			}
		}
	}
	return (0);
}

void	ft_putenv(char *var)
{
	extern char	**environ;
	char		**new_env;
	char		*var_;
	int			x;

	x = ft_findvar(var);
	if (x == -1)
	{
		x = 0;
		while (environ[x])
			x++;
		new_env = (char **) malloc((x + 2) * sizeof(char *));
		x = -1;
		while (environ[++x])
			new_env[x] = ft_strdup(environ[x]);
		var_ = ft_strdup(environ[--x]);
		new_env[x++] = ft_strdup(var);
		new_env[x++] = var_;
		new_env[x] = NULL;
		environ = new_env;
	}
	else
		environ[x] = ft_strdup(var);
}

void	ft_unputenv(char *name)
{
	int			x;
	extern char	**environ;

	x = ft_findvar(name);
	if (x > -1)
	{
		while (environ[x])
		{
			if (environ[x + 1])
				environ[x] = environ[x + 1];
			x++;
		}
		environ[--x] = NULL;
	}
}
