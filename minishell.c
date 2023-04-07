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
#include"minishell.h"
/*
void detect_command(char* command)
{
	if(!ft_strncmp(command, "pwd",4))
	{
		result = getcwd();
	}
	printf(%s);
}*/
void	init_mini_shell();

int ex;

void	handler(int sig, siginfo_t *info, void *n)
{
	char* command;
	if(sig == 2)
	{
		printf("\n");
		command = readline(">>> MiniShell $>");
		if(*command)
		{
			add_history(command);
			printf("%s\n", command);
		}
		free(command);
	}
	if(sig == 3)
	{
		ex = 1;
	}
}

void	init_mini_shell()
{

	while(!ex)
	{
		char* command;
		command = readline(">>> MiniShell $>");
		if(*command)
		{
			add_history(command);
			printf("%s\n", command);
		}
		free(command);
	}
	exit(0);
}

int	main()
{
	struct sigaction sign;

	sign.sa_flags = SA_RESTART;
	sign.sa_sigaction = &handler;
	sigaction(SIGINT, &sign, NULL);//ctr-C
	sigaction(SIGQUIT, &sign, NULL);//ctr-/
	init_mini_shell();
}
 //"e""c""h""o" hello need to work