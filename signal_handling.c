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

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		*g_error = 1;
		ft_printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
		*g_error = 0;
}

int	handle_signals(void)
{
	if (signal(SIGQUIT, handler))
		return (1);
	if (signal(SIGINT, handler))
		return (1);
	return (0);
}

void	handler2(int sig)
{
	if (sig == SIGINT)
	{
		*g_error = 1;
		ft_printf("AAAAAAAAAAAAAAA\n");
		kill(getpid(), SIGQUIT);
	}
}

	// if (!pid)
	// if (info->si_pid != pid)
	// 	pid = info->si_pid;
void	handler3(int sig, siginfo_t *info, void *uc)
{
	int		pid;

	(void)(uc);
	pid = info->si_pid;
	if (sig == SIGINT)
	{
		kill(pid, SIGTERM);
	}
}

	// if (signal(SIGINT, handler2))
	// 	return (1);
	// signal(SIGINT, SIG_DFL);
int	handle_heredoc_signals(void)
{
	struct sigaction	sig_act;

	sig_act.sa_sigaction = handler3;
	sig_act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGINT, &sig_act, NULL) < 0)
		ft_printf("failed to assign handler");
	return (0);
}
