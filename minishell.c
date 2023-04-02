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

#include <stdio.h>
#include <unistd.h>
# include <curses.h>

#define clear() printf("\033[H\033[J")

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
	printf("BOOOM!!\n");
}

void	init_shell()
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
::::::::::      ++++++++++++++++              ";
// char sh = "     
//            _.---._
//        .'"".'/|\`.""'.
//       :  .' / | \ `.  :
//       '.'  /  |  \  `.'
//        `. /   |   \ .'
//     jgs  `-.__|__.-'
// "

	clear();
	printf("\n**********************************************************\n");
	printf("\n**************\t Welcome to new shell \t**************\n\n%s\n",sh);
	sleep(5);
	clear();
}

int	main()
{
	init_shell();
	printf(">  ");
	while(1)
	{
		boom();
		pause();
	}
}
