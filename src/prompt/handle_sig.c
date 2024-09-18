/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sig.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:21:02 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/18 23:07:06 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t g_signal;

void	handle_sigint(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_signal = SIGINT;
	}
}

void	handle_signals(t_data *minishell)
{
	if (g_signal == SIGINT)
	{
		minishell->last_status = 130;
		g_signal = 0;
	}
	if (g_signal == SIGQUIT)
	{
		minishell->last_status = 131;
		g_signal = 0;
	}
}
