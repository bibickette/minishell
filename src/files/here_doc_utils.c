/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 03:32:14 by phwang            #+#    #+#             */
/*   Updated: 2024/09/24 22:04:27 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

int	init_dup_hd(int *std_in, int *std_inb)
{
	*std_in = dup(STDIN_FILENO);
	if (*std_in == -1)
		return (perror(DUP_SIMPLE_ERR), KO);
	*std_inb = dup(STDIN_FILENO);
	if (*std_inb == -1)
	{
		close_one_fd(*std_in);
		return (perror(DUP_SIMPLE_ERR), KO);
	}
	return (OK);
}

int	dup_db_hd(int to_dup, int std_inb, t_data *minishell)
{
	if (dup2(to_dup, STDIN_FILENO) < 0)
	{
		close_one_fd(minishell->fd_hd);
		close_one_fd(to_dup);
		close_one_fd(std_inb);
		perror(DUP_ERR);
		return (KO);
	}
	return (OK);
}

int	handle_no_line_hd(t_data *minishell, int std_in,
		int std_inb)
{
	close_one_fd(minishell->fd_hd);
	close_one_fd(std_in);
	if (dup_db_hd(std_inb, std_in, minishell) == KO)
		return (KO);
	close_one_fd(std_inb);
	if (g_signal == HD_STOP)
		g_signal = WAS_IN_HD;
	return (KO);
}
