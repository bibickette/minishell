/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:21:02 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/24 21:57:36 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

void	handle_signals(t_data *minishell)
{
	if ((g_signal == SIGINT || g_signal == WAS_IN_HD || g_signal == IN_HD
			|| (!(g_signal == IN_PARENT))) && g_signal != 0
		&& g_signal != CTRL_D)
		minishell->last_status = 130;
	if (g_signal == SIGQUIT)
		minishell->last_status = 131;
}

void	handle_sigquit(int signum)
{
	if (signum == SIGQUIT)
	{
		if (g_signal == IN_PARENT)
			ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
		g_signal = SIGQUIT;
	}
}

void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		if (g_signal == IN_HD)
		{
			write(1, "\n", 1);
			close(STDIN_FILENO);
			g_signal = HD_STOP;
			return ;
		}
		sigint_utils();
	}
}

void	sigint_utils(void)
{
	if (g_signal == IN_PARENT)
	{
		write(1, "\n", 1);
		g_signal = SIGINT;
	}
	else if (!(g_signal == IN_PARENT))
	{
		if (!(g_signal == WAS_IN_HD))
		{
			write(1, "\n", 1);
			g_signal = SIGINT;
		}
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
