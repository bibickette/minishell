/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_status_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 01:48:10 by phwang            #+#    #+#             */
/*   Updated: 2024/09/19 01:48:01 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

int	get_status_process(t_data *minishell, int *status, pid_t pid)
{
	handle_signals(minishell);
	if (minishell->nb_files > 0)
		close_all_files(minishell->files);
	waitpid(pid, &minishell->last_status, 0);
	minishell->last_status = WEXITSTATUS(*status);
	if (minishell->last_status != 0 && minishell->last_status != 127
		&& minishell->last_status != 126
		&& minishell->last_status != EXIT_FAILURE)
		return (minishell->last_status);
	return (minishell->last_status);
}
