/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohachami <ohachami@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 20:00:37 by ohachami          #+#    #+#             */
/*   Updated: 2023/04/08 20:00:39 by ohachami         ###   ########.fr       */
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
		error = 1;
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if(sig == SIGQUIT)
	{
		error = 0;
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
