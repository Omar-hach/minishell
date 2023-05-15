/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:14:18 by ohachami          #+#    #+#             */
/*   Updated: 2023/03/26 23:14:59 by ohachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h> 
# include <sys/ioctl.h>
# include <sys/wait.h>
# include <sys/stat.h> 
# include <signal.h>
# include <string.h>
# include <stdio.h>
# include <dirent.h>
# include <termios.h> 
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 600
# endif

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*uni;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!s1)
		return (NULL);
	uni = (char *)calloc(strlen (s1) + strlen (s2) + 1, 1);
	if (!uni)
		return (NULL);
	while (s1[++i])
		uni[i] = s1[i];
	while (s2[++j])
		uni[i + j] = s2[j];
	return (uni);
}

int	part_count(char *s, char c)
{
	int		part;

	part = 0;
	while (*s)
	{
		s++;
		if ((*s == c && *(s - 1) != c) || (*s == '\0' && *(s - 1) != c))
			part++;
	}
	return (part);
}

int	*word_len(char *s, char c, int part)
{
	int		*array;
	int		i;

	array = (int *)malloc(part * sizeof(int));
	i = 0;
	while (*s)
	{
		array[i] = 1;
		while (*s == c)
			s++;
		while (*s != c && *s)
		{
			array[i]++;
			s++;
		}
		if (!*s || i >= part - 1)
			break ;
		i++;
	}
	return (array);
}

char	**word_cutter(char *s, char c, char **array)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	while (s[k])
	{
		if (s[k] != c)
		{
			array[i][j] = s[k];
			j++;
			if (s[k + 1] == c)
			{
				i++;
				j = 0;
			}
		}
		k++;
	}
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		i;
	int		*len_array;
	int		part;

	i = 0;
	if (!s)
		return (NULL);
	part = part_count((char *)s, c);
	array = (char **)malloc((part + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	if (part == 0)
		len_array = NULL;
	else
		len_array = word_len((char *)s, c, part);
	while (i < part)
	{
		array[i] = (char *)calloc(len_array[i], sizeof(char));
		i++;
	}
	array = word_cutter((char *)s, c, array);
	array[i] = NULL;
	free(len_array);
	return (array);
}

int	ft_strlen_b(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_bzero_b(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(char *)s = 0;
		s++;
		i++;
	}
}

void	*ft_calloc_b(size_t count, size_t size)
{
	void	*p;

	p = malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero_b(p, count * size);
	return (p);
}

char	*ft_strjoin_b(char *s1, char *s2)
{
	char	*uni;
	int		i;
	int		j;

	if (!s1)
	{
		s1 = ft_calloc_b(1, 1);
		*s1 = '\0';
	}
	i = -1;
	j = -1;
	uni = (char *)ft_calloc_b(ft_strlen_b(s1) + ft_strlen_b(s2) + 1, 1);
	if (!uni)
	{
		free(s1);
		return (NULL);
	}
	while (s1[++i])
		uni[i] = s1[i];
	while (s2[++j])
		uni[i + j] = s2[j];
	free(s1);
	return (uni);
}

int	check_rest(char *rest)
{
	int	i;

	i = 0;
	while (rest[i])
	{
		if (rest[i] == '\n')
			return (i + 1);
		i++;
	}
	return (0);
}

char	*detect_new_line(char *line, char *buff, int fd, int *k)
{
	int		len;
	ssize_t	i;

	i = 1;
	while (i > 0)
	{
		len = 0;
		if (buff != NULL)
			line = ft_strjoin_b(line, buff);
		while (line[len])
		{
			if (line[len] == '\n')
				break ;
			len++;
		}
		*k = len + 2;
		if (line[len] == '\n')
			break ;
		i = read(fd, buff, BUFFER_SIZE);
		if (i > 0)
			buff[i] = '\0';
		if (i < 0)
			break ;
	}
	return (line);
}

char	*get_rest_and_line(char *line, char *rest, int k)
{
	int		i;
	char	*result;

	i = 0;
	result = ft_calloc_b(k + 1, 1);
	while (line[i] != '\n' && line[i])
	{
		result[i] = line[i];
		i++;
	}
	result[i] = line[i];
	if (line[i])
		i++;
	k = 0;
	while (line[i])
	{
		rest[k] = line[i];
		i++;
		k++;
	}
	rest[k] = '\0';
	free (line);
	line = NULL;
	return (result);
}

char	*gnl(char *rest, char *buff, int fd)
{
	int		count;
	char	*line;

	line = NULL;
	count = 0;
	if (*rest)
		line = ft_strjoin_b(line, rest);
	line = detect_new_line(line, buff, fd, &count);
	if (buff != NULL)
		free(buff);
	return (get_rest_and_line(line, rest, count));
}
# include <limits.h>

char	*get_next_line(int fd)
{
	ssize_t		i;
	char		*buff;
	static char	rest[FOPEN_MAX][BUFFER_SIZE + 1];
	int			count;

	if (fd < 0)
		return (NULL);
	count = check_rest(rest[fd]);
	i = 1;
	if (!count)
	{
		buff = ft_calloc_b(BUFFER_SIZE + 1, 1);
		i = read(fd, buff, BUFFER_SIZE);
		if (i == -1)
			ft_bzero_b(rest[fd], BUFFER_SIZE);
	}
	else
		buff = NULL;
	if (i <= 0 && !(*rest[fd]))
	{
		free(buff);
		return (NULL);
	}
	return (gnl(rest[fd], buff, fd));
}


typedef struct s_token
{
	int		token;
	char	*arg;//**arg;
	int		redir;
	char	*out;
}t_token;

// echo hey 26h2g61h | ls

typedef struct s_tree
{
	int				indix;
	struct s_tree	*father;
	struct s_tree	*left_son;
	struct s_tree	*right_son;
}t_tree;

typedef struct s_lexic
{
	char	**l_cmd;
	char	**l_symb;
}t_lexic;

void	*free_aray(char	**words)
{
	int	i;

	i = -1;
	while (words[++i])
		free(words[i]);
	free(words);
	return (NULL);
}

int	creat_lexic(t_lexic *lex)
{
	lex->l_cmd = (char **)malloc(8 * sizeof(char *));
	if (!lex->l_cmd)
		return (1);
	lex->l_cmd[0] = strdup("env");//11
	lex->l_cmd[1] = strdup("pwd");
	lex->l_cmd[2] = strdup("cd");
	lex->l_cmd[3] = strdup("exit");
	lex->l_cmd[4] = strdup("export");
	lex->l_cmd[5] = strdup("unset");
	lex->l_cmd[6] = strdup("echo");//17
	lex->l_cmd[7] = NULL;
	lex->l_symb = (char **)malloc(6 * sizeof(char *));
	if (!lex->l_cmd)
	{
		free_aray(lex->l_cmd);
		return (1);
	}
	lex->l_symb[0] = strdup("|");//21
	lex->l_symb[1] = strdup("<<");
	lex->l_symb[2] = strdup("<");
	lex->l_symb[3] = strdup(">>");
	lex->l_symb[4] = strdup(">");//25
	lex->l_symb[5] = NULL;
	return (0);
}



void	*free_struct_array(char **words, t_lexic *lex, t_token *nodes, int len)
{
	int	i;

	i = -1;
	while (nodes && ++i < len)
	{
		printf("arg=%p, len=%d\n", nodes[i].arg, len);
		if (nodes[i].arg)
			free(nodes[i].arg);
	}
	if (nodes)
		free(nodes);
	if (words)
		free_aray(words);
	if (lex && lex->l_cmd)
		free_aray(lex->l_cmd);
	if (lex && lex->l_symb)
		free_aray(lex->l_symb);
	return (NULL);
}

int	count_space(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ((s[i] == ' ') || (s[i] == '\t')))
		i++;
	return (i);
}

int	ft_find(char *s, char **token)
{
	int	i;
	int	diff;

	i = -1;
	diff = 0;
	while (token[++i])
	{
		diff = strncmp(token[i], s, strlen(token[i]));
		if (!diff)
			return (i + 1);
	}
	return (0);
}

int	error_print(char *message, char *prob, int n)
{
	printf("%s '", message);
	while (*prob && n--)
	{
		printf("%c", *prob);
		prob++;
	}
	printf("'\n");
	return (1);
}

int	last_char(char *s, int queot, int double_qu)
{
	while (*s == ' ' || *s == '\t')
		s--;
	if (queot % 2)
	{
		printf("minshell: error unexpected token %c\n", 34);
		return (1);
	}
	if (double_qu % 2)
	{
		printf("minshell: error unexpected token %c\n", 39);
		return (1);
	}
	if (*s == '>' || *s == '|' || *s == '<')
	{
		printf("minshell: error unexpected token `%c", *s);
		if ((*(s - 1) == '>' && *s == '>') || (*(s - 1) == '>' && *s == '>'))
			printf("%c", *(s - 1));
		printf("'\n");
		return (1);
	}
	return (0);
}

int	detect_sym_error(char *s, char **sym, int *part)
{
	int	queot;
	int	double_qu;

	queot = 0;
	double_qu = 0;
	if (ft_find(s + count_space(s), sym))
		return (error_print("minshell: error unexpected token",
				sym[ft_find(s, sym) - 1], 2));
	while (*s)
	{
		queot += (*s == 34) * !(double_qu % 2);
		double_qu += (*s == 39) * !(queot % 2);
		if ((*s == ';' || *s == 92) && !(queot % 2) && !(double_qu % 2))
			return (error_print("minshell: error unexpected token", s, 1));
		if (*(++s) && ft_find(s, sym) && !(queot % 2) && !(double_qu % 2))
		{
			s += strlen(sym[ft_find(s, sym) - 1]);
			s += count_space(s);
			if (ft_find(s, sym))
				return (error_print("minshell: error unexpected token",
						sym[ft_find(s, sym) - 1], 2));
			*part += 2;
		}
	}
	return (last_char(s - 1, queot, double_qu));
}

int	get_symb_len(int sym_type, char *s, char **sym)
{
	int	queot;
	int	double_qu;
	int	count;

	queot = 0;
	double_qu = 0;
	count = 0;
	if (sym_type == 0)
		return (1);
	else if (sym_type == 1 || sym_type == 3)
		count = 2 + count_space(s + 2);
	else if (sym_type == 2 || sym_type > 3)
		count = 1 + count_space(s + 1);
	while ((!ft_find(s + count, sym) && (s[count] != ' ' && s[count] != '\t')
			&& s[count]) || (((queot % 2) || (double_qu % 2)) && s[count]))
	{
		queot += (*(s + count) == 34) * !(double_qu % 2);
		double_qu += (*(s + count) == 39) * !(queot % 2);
		count++;
	}
	return (count);
}

int	get_token_len(char *s, char **sym)
{
	int	queot;
	int	double_qu;
	int	count;

	queot = 0;
	double_qu = 0;
	count = 0;
	while (*(s))
	{
		queot += (*s == 34) * !(double_qu % 2);
		double_qu += (*s == 39) * !(queot % 2);
		if (ft_find(s, sym) && !(queot % 2) && !(double_qu % 2))
			break ;
		count++;
		s++;
	}
	return (count);
}

int	*words_len(char *s, char **sym, int part)
{
	int	*array;
	int	i;

	array = (int *)calloc(part * 2, sizeof(int));
	if (!array)
		return (NULL);
	i = 0;
	while (*s && i < part)
	{
		array[i] = get_token_len(s, sym);
		s += array[i];
		s += count_space(s);
		if (++i < part && ft_find(s, sym))
			array[i] = get_symb_len(ft_find(s, sym) - 1, s, sym);
		if (i < part)
			s += array[i++];
	}
	return (array);
}

char	**words_cutter(char *s, int *len_array, char **array)
{
	int		i;
	int		l;
	int		j;
	int		k;

	l = len_array[0];
	i = 0;
	j = -1;
	k = 0;
	while (s[k])
	{
		if (len_array[i] != 0)
			array[i][++j] = s[k++];
		if (--len_array[i] < 1)
		{
			array[i][++j] = '\0';
			i++;
			j = -1;
			l += len_array[i] + 1;
		}
	}
	return (array);
}

char	**expr_split(char *s, char **sym, int part)
{
	char	**array;
	int		*len_array;
	int		i;

	array = NULL;
	if (detect_sym_error(s, sym, &part))
		return (NULL);
	array = (char **)calloc(part + 1, sizeof(char *));
	if (!array)
		return (NULL);
	len_array = words_len(s, sym, part);
	if (!len_array)
	{
		free(array);
		return (NULL);
	}
	i = -1;
	while (++i < part)
		array[i] = (char *)calloc(len_array[i] + 1, sizeof(char));
	array = words_cutter(s, len_array, array);
	array[part] = NULL;
	free(len_array);
	return (array);
}
char	*mint_dollars(char *s, int start, int name_len, char *val)
{
	int		size;
	char	*no_money;
	int		x;
	int		y;

	size = strlen(s) - name_len + strlen(val) + 1;
	no_money = (char *) malloc (size * sizeof(char));
	x = -1;
	while (++x <= start)
		no_money[x] = s[x];
	y = 0;
	while (y < strlen(val))
	{
		no_money[x + y] = val[y];
		y++;
	}
	y += x;
	x += name_len + 1;
	while (x < size)
		no_money[y++] = s[x++];
	no_money[x] = '\0';
	return (no_money);
}

char	*tax_dollars(char *s, int start, int name_len)
{
	int		x;
	int		y;

	x = 0;
	while (x <= start)
		x++;
	y = x + name_len + 1;
	while (s[y])
		s[x++] = s[y++];
	s[x] = '\0';
	return (s);
}

// get start and lenght of dolar var

char	*get_dollars(char *s, int x)
{
	int		y;
	int		z;
	char	*name;
	char	*val;
	char	*out;

	y = x;
	z = 0;
	while (s[++x] && s[x] != ' ' && s[x] != '$')
		z++;
	if (z < 1)
		return (s);
	name = (char *) malloc (z * sizeof(char));
	x = y;
	z = 0;
	while (s[++x] && s[x] != ' ' && s[x] != '$')
		name[z++] = s[x];
	name[z] = '\0';
	val = getenv(name);
	if (!val)
		out = tax_dollars(s, y - 1, z);
	else
		out = mint_dollars(s, y - 1, z, val);
	return (out);
}

// search for all  dolar var
// echo "'$PWD'" --> '/Users/ohachami/Documents/repo_git/minishell'
// echo '"$PWD"' --> '$PWD'
char	*replace_dollars(char *s)
{
	int		x;
	char	*out;

	x = 0;
	while (s[x] && s[x] != '$')// do skip queut
		x++;
	if (x == strlen(s))
		return (s);
	out = s;
	x = -1;
	while (out[++x])
	{
		if (out[x] == '$')
			out = get_dollars(out, x);
	}
	free(s);
	return (out);
}

t_token	*malloc_nodes(t_token *nodes, int len, t_lexic *lex)
{
	int	i;

	i = -1;
	nodes = (t_token *)calloc(len, sizeof(t_token));
	if (!nodes)
		return (free_struct_array(NULL, lex, nodes, len));
	while (++i < len)
	{
		nodes[i].token = 0;
		nodes[i].arg = NULL;
		nodes[i].redir = -1;
	}
	return (nodes);
}

int	nodes_count(char **word)
{
	int	i;
	int	part;

	i = -1;
	part = 0;
	while (word[++i])
	{
		printf("'%s' ", word[i]);
		if (word[i][0] != '>' && word[i][0] != '<')
			part++;
	}
	printf("\npart=%d\n", part);
	return (part);
}



char	*fill_cmd(char *word, int j, int i)
{
	char	*cmd;

	cmd = (char *)calloc(++i, sizeof(char));
	if (!cmd)
		return (NULL);
	i = -1;
	while ((word[++i] != ' ' && word[i] != '\t') && word[i])
	{
		while (word[i] == 34 || word[i] == 39)
			i++;
		cmd[j] = word[i];
		j++;
	}
	cmd[j] = '\0';
	return (cmd);
}

char	*fill_symb(char *word, int j, int *i)
{
	char	*sym;

	(*i) = -1;
	j = 1;
	if ((word[0] == '>' && word[1] == '>')
		|| (word[0] == '<' && word[1] == '<'))
		j = 2;
	sym = (char *)calloc(j + 1, sizeof(char));
	while (++(*i) < j)
		sym[(*i)] = word[(*i)];
	sym[j] = '\0';
	return (sym);
}

//yassir code

char	*find_path(char *file, int x, int y, int z)
{
	char	*path;
	char	**all_paths;

	all_paths = ft_split(getenv("PATH"), ':');
	path = NULL;
	while (all_paths[++x] && !path)
	{
		y = -1;
		z = -1;
		path = (char *)calloc(strlen(all_paths[x])
				+ strlen(file) + 2, 1);
		while (all_paths[x][++y])
			path[y] = all_paths[x][y];
		path[y++] = '/';
		while (file[++z])
			path[y + z] = file[z];
		path[y + z] = '\0';
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	free_aray(all_paths);
	return (path);
}

//echo "hello    ">a   b   c --> cat a : helo b c
char	*cmd_split(char *word, int *token, t_lexic lex, int type)
{
	int		i;
	int		j;
	char	*cmd;
	char	*arg;
	char	*bin;

	i = 0;
	j = 0;
	word += count_space(word);
	if (*word == '|')
	{
		*token = 21;
		return (NULL);
	}
	while (word[i] != ' ' && word[i] != '\t' && word[i] != '\0')
		i++;
	printf("cmd[]=%s.%d\n", word, type);
	word = replace_dollars(word); //$ management
	if (type == 21 || type < 1)
		cmd = fill_cmd(word, j, i);
	if ((type > 0 && type < 20) || type > 21)
		cmd = fill_symb(word, j, &i);
	if (!cmd)
		return (NULL);
	bin = find_path(cmd, -1, -1, -1);
	//token detection
	if (ft_find(cmd, lex.l_cmd)
		&& strlen(lex.l_cmd[ft_find(cmd, lex.l_cmd) - 1]) == strlen(cmd)){
		*token = ft_find(cmd, lex.l_cmd) + 10;}
	else if (ft_find(cmd, lex.l_symb) && (type > 21 || type < 20)) //probleme here
		*token = ft_find(cmd, lex.l_symb) + 20;
	else if (strchr(cmd, '/'))
	{
		*token = 1;
		arg = (char *)calloc(strlen(word) + 1, sizeof(char));
		memcpy(arg, word, strlen(word) + 1);
		return (arg);
	}
	else if (bin)
	{
		*token = 1;
		arg = (char *)calloc(strlen(bin) + strlen(word) + 1,
				sizeof(char));
		i = strlen(bin) - strlen(cmd);
		j = -1;
		while (++j < i)
			arg[j] = bin[j];
		memcpy(&arg[j], word, strlen(word) + 1);
		free(cmd);
		free(bin);
		return (arg);
	}
	else
	{
		printf("minshell: %s :command not found\n", cmd);
		free(cmd);
		return (NULL);
	}
	printf("cmd[%d]=%s\n", i, cmd);
	//fill arg
	i = strlen(cmd);
	arg = (char *)calloc(strlen(word + i) - count_space(word + i) + 1,
			sizeof(char));
	if (!arg)
	{
		free(cmd);
		return (NULL);
	}
	word += count_space(word + i) + i;
	i = -1;
	while (word[++i]) //handle arg to **arg with no ""
		arg[i] = word[i];
	arg[i] = '\0';
	//free the rest
	free(cmd);
	if (bin)
		free(bin);
	return (arg);
}

t_token	*fill_nodes(char **words, t_lexic *lex, t_token *nodes,  int *len)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	j = 0;
	k = 0;
	if(!nodes)
		*len = -1;
	while (words[++i] && nodes)
	{
		nodes[j].arg = cmd_split(words[i], &nodes[j].token, *lex,
				(j > 0) * nodes[j - 1].token);
		printf("i=%d j =%d k=%d arg=%s\n", i, j, k, nodes[j].arg);
		if (!nodes[i].arg && nodes[j].token == 0)
			return (free_struct_array(words, lex, nodes, *len));//127
		if (nodes[j].token > 21)
			nodes[k].arg = ft_strjoin(nodes[k].arg, words[(i++) + 1]);
		if (nodes[j].token == 21)
			k = i;
		j++;
	}
	return (nodes);
}

t_token	*split_input(char *input, int *len)
{
	int		i;
	t_lexic	lex;
	t_token	*nodes;
	char	**words;

	if (creat_lexic(&lex))
		return (NULL);
	i = 1;
	words = expr_split(input, lex.l_symb, i);
	if (!words)
		return (free_struct_array(NULL, &lex, NULL, -1));
	*len = nodes_count(words);
	nodes = NULL;
	nodes = malloc_nodes(nodes, *len, &lex);
	if (!fill_nodes(words, &lex, nodes, len))
		return (NULL);
	i = -1;
	while (++i < (*len))
		printf("i =%d type=%d <%s>\n", i, nodes[i].token, nodes[i].arg);
	free_struct_array(words, &lex, NULL, -1);
	return (nodes);
}
//<cmd><|><exp>
t_tree	*new_branch(int data)
{
	t_tree	*tree;

	tree = (t_tree *)calloc(1, sizeof(t_tree));
	tree->indix = data;
	tree->father = NULL;
	tree->left_son = NULL;
	tree->right_son = NULL;
	return (tree);
}

void	treeprint(t_tree *root, int level, t_token *nodes)
{
	int	i;

	i = 7;
	if (root == NULL)
		return ;
	level += 8;
	treeprint(root->right_son, level, nodes);
	printf("\n");
	while (++i < level)
	{
		printf(" ");
	}
	printf("%d=%s-->left=%p-->right=%p\n", nodes[root->indix].token, nodes[root->indix].arg, root->left_son, root->right_son);
	treeprint(root->left_son, level, nodes);
	//free(root);
}

t_tree	*create_tree(t_token *nodes, int len)
{
	t_tree	*branch;
	t_tree	*root;
	t_tree	*tree;
	int		*list;
	int		i;

	i = -1;
	list = (int *)calloc(len + 1, sizeof(int));
	list[len] = -1;
	while (list[++i] > -1)
		list[i] = nodes[i].token;
	i = 0;
	root = new_branch(i++);
	while (list[i] > -1)
	{
		branch = new_branch(i);
		if (list[i] < 19)
		{
			if (!root->left_son)
				root->left_son = branch;
			else
				root->right_son = branch;
			branch->father = root;
		}
		if (list[i] == 22 || list[i] == 23)
		{
			while (root->father && list[root->father->indix] == 21)
				root = root->father;
			if (list[root->indix] != 21)
				list[i] = 26;
			else
			{
				printf("here\n");
				branch->father = root;
				branch->left_son = root->left_son;
				root->left_son = branch;
				branch->left_son->father = branch;
			}
		}
		if (list[i] == 21 || list[i] > 23)
		{
			while (root->father)
				root = root->father;
			root->father = branch;
			branch->right_son = root;
		}
		root = branch;
		i++;
	}
	tree = root;
	while (tree->father)
		tree = tree->father;
	free(list);
	return (tree);
}

int	main(void)
{
	char	*input;
	int		ex;
	t_token	*nodes;
	t_tree	*tree;
	int file = open("text.txt", O_RDONLY);

	ex = 1;
	tree = NULL;
	nodes = NULL;
	while (ex)
	{
		printf(">>> MiniShell $>");
		input = get_next_line(file);
		if (!input)
			break ;
		if (*(input + count_space(input)))
		{
			input[strlen(input) - 1] = '\0';
			nodes = split_input(input, &ex);
			if (nodes)
			{
				tree = create_tree(nodes, ex);
				treeprint(tree, 0, nodes);
				free_struct_array(NULL, NULL, nodes, ex);
				ex = 1;
			}
		}
		free(input);
		//system("leaks minishell");
	}
	exit(1);
}
 //"e""c""h""o" hello need to work
 // error file name too long.