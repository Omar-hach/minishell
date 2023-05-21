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
/*# include "minshell.h"

void	handler(int sig, siginfo_t *info, void *n)
{
	if(sig == 2)
	{
		start_mini_shell();
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
}*/
