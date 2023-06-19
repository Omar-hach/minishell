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
}

int	handle_signals(void)
{
	if (signal(SIGQUIT, SIG_IGN))
		return (1);
	if (signal(SIGINT, handler))
		return (1);
	return (0);
}
