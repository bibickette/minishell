/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:33:28 by phwang            #+#    #+#             */
/*   Updated: 2024/09/19 14:36:20 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

void	do_single_fork(t_data *minish, t_list *token, int *pid)
{
	g_signal = IN_PARENT;
	if (*pid == KO)
	{
		minish->last_status = errno;
		return (ft_putstr_fd(FORK_ERR, STDERR_FILENO));
	}
	if (*pid == 0)
		child_single_fork(minish, token);
}

void	child_single_fork(t_data *minish, t_list *token)
{
	char	*path;
	char	**arg;

	arg = NULL;
	path = NULL;
	if (open_all_infile(minish) == KO || !minish->command_tab
		|| !minish->command_tab[0]
		|| check_cmd_value(minish->command_tab[0]) == KO)
		exit(execve_error_free(minish, arg, path, token));
	path = split_n_path(minish, &arg, 0, token);
	if (redirection_in(minish, minish->files, STDIN_FILENO) != OK
		|| open_all_outfile(minish) == KO || redirection_out(minish,
			minish->files, STDOUT_FILENO) != OK)
		exit(execve_error_free(minish, arg, path, token));
	if (minish->nb_files > 0)
		close_all_files(minish->files);
	if (execve(path, arg, minish->builtins->env) == KO)
		execve_error(minish, path, arg, token);
	exit(EXIT_SUCCESS);
}
