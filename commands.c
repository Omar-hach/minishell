#include"minishell.h"

extern char	**environ;
char		*working_dir;

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
	out[i + 1] = '\0';
	return (out);
}

char	*ft_env()
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
	else if (flag == 0)
		out = ft_strdup_newline(arg);
	return (out);
}

char	*ft_pwd()
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

char	*ft_cd(char *arg)
{
	DIR	*dir;

	dir = opendir(arg);
	if (dir)
	{
		working_dir = (char *) dir;
		return ("");
	}
	else
		return ("dir don exist");
}

void	ft_export(){}

void	ft_unset(){}

void	ft_exit(){}

/*
void	get_last_son_father(t_tree *tree)
{
	while (tree->left_son->left_son)
	{
		tree = tree->left_son;
	}
}
*/

char	*exec_cmd(t_token token)
{
	char	*out;

	if (token.type == 11)
		out = ft_env();
	if (token.type == 12)
		out = ft_pwd();
	if (token.type == 13)
		out = ft_cd(token.arg);
	if (token.type == 17)
		out = ft_echo(token.arg, 0);
	return (out);
}

char	*ft_pipe(t_token l, t_token r)
{
	//char	*in;
	char	*out;

	r.arg = exec_cmd(l);
	out = exec_cmd(r);
	return (out);
}

void	ft_redirect_in(){}

void	ft_redirect_in_append(){}

void	ft_redirect_out(){}

void	ft_redirect_out_append(){}

void	ft_var()
{
}

char	*exec_prog(t_token token)
{
	char	*prog_name;
	char	**prog_argv;
	char	**prog_envp = NULL;
	//char	*prog_envp[] = { "some", "environment", NULL };
	int	x;
	char	*out;

	prog_argv = ft_split(token.arg, ' ');
	prog_name = ft_strdup(prog_argv[0]);
	ft_printf("%d prog name = %s, args = %s %s %s\n", x, prog_name, prog_argv[0], prog_argv[1], prog_argv[2]);
	execve(prog_name, prog_argv, prog_envp);
	return ("");
}

char	*exec_symbol(t_token *token, int x, t_tree *lson, t_tree *rson)
{
	char	*out;
	int	l;
	int	r;

	l = lson->token_index;
	r = rson->token_index;
	if (token[x].type == 20)
		out = ft_pipe(token[l],token[r]);
	if (token[x].type == 21)
		ft_redirect_in();
	return (out);
}

char	*exec_tree(t_tree *tree, t_token *tokens)
{
	int	x;
	int	i;
	char	*in;
	char	*out;

	i = 0;
	//tree = get_last_son_father(tree);
	//while (tree->left_son)
	//	tree = tree->left_son;
	//if (tree->father)
	//	tree = tree->father;
	x = tree->token_index;
	//printf("%d\n", tokens[x].type / 10);
	if (tokens[x].type == 1)
		out = exec_prog(tokens[x]);
	else if (tokens[x].type / 10 == 1)
		out = exec_cmd(tokens[x]);
	else if (tokens[x].type / 10 == 2)
	{
		//while (tree->father)
		//{
			//out = ft_strdup("symb");
			out = exec_symbol(tokens, x, tree->left_son, tree->right_son);
		//	tree = tree->father;
		//	x = tree->token_index;
		//}
	}
	return (out);
}

//              0
//             / \
//            /   \
//           1     2
//          / \
//         /   \
//        3     4

int main() {
	t_tree	*tree;
	t_token	*token;

	tree = (t_tree *) malloc(sizeof(t_tree));
	tree->token_index = 0;

	tree->father = NULL;
	tree->right_son = NULL;	
	tree->left_son = NULL;
/*
	tree->right_son = (t_tree *) malloc(sizeof(t_tree));
	tree->right_son->token_index = 2;
	tree->right_son->father = tree;
	tree->right_son->right_son = 0;
	tree->right_son->left_son = 0;

	tree->left_son = (t_tree *) malloc(sizeof(t_tree));
	tree->left_son->token_index = 1;
	tree->left_son->father = tree;
	tree->left_son->right_son = 0;
	tree->left_son->left_son = 0;
*/	
/*	tree->left_son->right_son = (t_tree *) malloc(sizeof(t_tree));
	tree->left_son->right_son->token_index = 4;
	tree->left_son->right_son->father = tree->left_son;
	tree->left_son->right_son->right_son = 0;
	tree->left_son->right_son->left_son = 0;

	tree->left_son->left_son->right_son = (t_tree *) malloc(sizeof(t_tree));
	tree->left_son->left_son->right_son->token_index = 3;
	tree->left_son->left_son->father = tree->left_son;
	tree->left_son->left_son->right_son = 0;
	tree->left_son->left_son->left_son = 0;
*/
//	ft_printf("treeed");

	token = (t_token *) malloc(5 * sizeof(t_token));
	token[0].type = 1;
	//token[0].arg = 0;
	token[0].arg = ft_strdup("/bin/ls");
	token[0].in = 0;
	token[0].out = 0;

	token[1].type = 16;
	//token[1].arg = 0;
	token[1].arg = ft_strdup("hello1");
	token[1].in = 0;
	token[1].out = 0;

	token[2].type = 11;
	//token[2].arg = 0;
	token[2].arg = ft_strdup("hello2");
	token[2].in = 0;
	token[2].out = 0;

	token[3].type = 16;
	//token[1].arg = 0;
	token[3].arg = ft_strdup("hello3");
	token[3].in = 0;
	token[3].out = 0;

	token[4].type = 11;
	//token[2].arg = 0;
	token[4].arg = ft_strdup("hello4");
	token[4].in = 0;
	token[4].out = 0;

	ft_printf("out = %s", exec_tree(tree, token));
}
