/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 22:30:09 by yhachami          #+#    #+#             */
/*   Updated: 2023/03/30 22:38:40 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	boom()
{
	int x;

	x = 4;
	printf("explode in\n");
	while(--x > 0)
	{
		printf("%d...\n",x);
		sleep(1);
	}
	printf("BOOOM!!\n\n");
}

void	start_shell()
{
	char *sh = " \n\
                    ++                        \n\
                  ++  ++                      \n\
                  ++    ++                    \n\
                ++....  ++  ++    ++++++      \n\
              ++++........++++++++    ++      \n\
            ++  ++++++++++++++..    ++        \n\
  ++++++++++++++++++++++++++....    ++++++    \n\
  ++    ..++++++++  ++++++++++....++++++  ++  \n\
    ++    ....++++    ..++++++++++++++....++  \n\
    ++......++++++  ....++++++++++..      ..++\n\
      ++..++++++++....++++++++++..      ..  ++\n\
    ++++++++++++++++++++++++++      ..####  ++\n\
    ++    ::::::::::::++++..      ########..++\n\
    ++..::....      ..::      ..##########..++\n\
    ++::..            ::  ..####::######++++  \n\
    ::::::..        ::##########..++##++++++  \n\
  ::..            ::##++::####++::..::++++    \n\
  ::          ..::::..::++....::++++++++      \n\
::..  ....::::::::++++::::++++++++++          \n\
::::::::::      ++++++++++++++++              \n";
// char sh = "     
//            _.---._
//        .'"".'/|\`.""'.
//       :  .' / | \ `.  :
//       '.'  /  |  \  `.'
//        `. /   |   \ .'
//   SHELL  `-.__|__.-'
// "

	printf("\033[H\033[J");
	printf("%s\n**********************************************************\n",sh);
	printf("\n**************\t Welcome to new shell \t**************\n\n");
	boom();
}

/*
void detect_command(char* command)
{
	if(!ft_strncmp(command, "pwd",4))
	{
		result = getcwd();
	}
	printf(%s);
}*/

// get cammads and tokens

void get_input(t_input in, char *input)
{
	in.command = (t_command *) malloc(3 * sizeof(t_command));

	in.command[0].cmd = input;
}

void	init_mini_shell()
{
	t_input in;
	char *input;

	while(!ex)
	{
		input = readline(">>> Shell $>");
		get_input(in, input);
		if(in.command[0].cmd)
		{
			add_history(in.command[0].cmd);
			printf("%s\n", in.command[0].cmd);
			free(input);
		}
	}
}

void	handler(int sig, siginfo_t *info, void *n)
{
	if(sig == 2)
	{
		init_mini_shell();
	}
	if(sig == SIGQUIT)
	{
		ex = 1;
	}
}

void handle_signals()
{
	struct sigaction sign;

	sign.sa_flags = SA_RESTART;
	sign.sa_sigaction = &handler;
	sigaction(SIGINT, &sign, NULL);//ctr-C
	sigaction(SIGQUIT, &sign, NULL);//ctr-/
}

int	main()
{
	handle_signals();
	start_shell();
	init_mini_shell();
}
 //"e""c""h""o" hello need to work
