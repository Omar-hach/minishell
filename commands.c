#include"minishell.h"

extern char **environ;

char	*join_args(char **args, char between)
{
	int	x;
	int	i;
	int	j;
	int	size;
	char	*out;

	size = 0;
	i = -1;
	while (args[++i])
		size += ft_strlen(args[i]) + 1;
	out = (char *) malloc(size * sizeof(char));
	x = -1;
	i = -1;
	while (args[++i])
	{
		j = -1;
		while (args[i][++j])
			out[++x] = args[i][j];
		out[++x] = between;
	}
	out[x] = '\0';
	return (out);
}

char	*ft_strdup_newline(char *s)
{
	int	i;
	int	size;
	char	*out;

	size = ft_strlen(s) + 1;
	out = (char *) malloc(size * sizeof(char));
	i = -1;
	while (s[++i])
		out[i] = s[i];
	out[i] = '\n';
	return (out);
}

char	*env()
{
	int	i;
	int	x;
	char	**s;
	char	*out;

	s = environ;
	i = -1;
	x = -1;
	while (s[++i])
		out = join_args(s, '\n');
	return (out);
}

char	*ft_echo(char *arg, char flag)
{
	char	*out;

	if (flag == 'n')
		out = ft_strdup(arg);
	else
		out = ft_strdup_newline(arg);
	return (out);
}

char	*pwd()
{
	char	*dir;
	int	i;

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
	return (dir);
}

void	cd(char *arg)
{
	int i;

	i = 0;
}

int main() { printf("%s", pwd());}
