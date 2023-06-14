/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhachami <yhachami@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:00:37 by ohachami          #+#    #+#             */
/*   Updated: 2023/06/13 21:30:01 by yhachami         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	handler(int sig, siginfo_t *info, void *n)
{
	int i=info->si_pid;
	i=0;
	(void)n;
	if(sig == SIGINT)
	{
<<<<<<< HEAD
		*g_error = 1;
=======
		error = 1;
>>>>>>> fbd9d4fbcef0fb6c92e25959365619fd3c037921
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if(sig == SIGQUIT)
	{
<<<<<<< HEAD
		*g_error = 0;
=======
		error = 0;
>>>>>>> fbd9d4fbcef0fb6c92e25959365619fd3c037921
	}
}

int handle_signals(void)
{
	struct sigaction sign;

	sign.sa_flags = SA_SIGINFO;
	sign.sa_sigaction = &handler;
	if(sigaction(SIGINT, &sign, NULL) &&/*ctr-C*/ sigaction(SIGUSR1, &sign, NULL))//ctr-/
		return(1);
	return(0);
}
