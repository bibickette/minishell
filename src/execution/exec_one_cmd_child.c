/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:33:28 by phwang            #+#    #+#             */
/*   Updated: 2024/09/25 20:42:15 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

void	do_single_fork(t_data *minish, t_list *token, t_cmd *cmd, int *pid)
{
	if (*pid == KO)
	{
		minish->last_status = errno;
		return (ft_putstr_fd(FORK_ERR, STDERR_FILENO));
	}
	if (*pid == 0)
		child_single_fork(minish, token, cmd);
}

void	child_single_fork(t_data *minish, t_list *token, t_cmd *cmd)
{
	char	*path;

	path = NULL;
	if (!cmd->cmd || !cmd->cmd[0])
	{
		execve_error_free(minish, path, token);
		exit(EXIT_SUCCESS);
	}
	if (open_all_infile(minish, cmd) == KO || !cmd->cmd || !cmd->cmd[0]
		|| check_cmd_value(cmd->cmd) == KO)
		exit(execve_error_free(minish, path, token));
	path = split_n_path(minish, cmd, token);
	if (redirection_in(minish, minish->files, cmd, STDIN_FILENO) != OK
		|| open_all_outfile(minish, cmd) == KO || redirection_out(cmd,
			cmd->files, STDOUT_FILENO) != OK)
		exit(execve_error_free(minish, path, token));
	if (minish->nb_hd_files > 0)
		close_all_files(minish->files);
	if (cmd->nb_files > 0)
		close_all_files(cmd->files);
	if (execve(path, cmd->cmd_args, minish->builtins->env) == KO)
		execve_error(minish, path, token);
	exit(EXIT_SUCCESS);
}
