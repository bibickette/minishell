/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd_child.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:33:28 by phwang            #+#    #+#             */
/*   Updated: 2024/09/14 17:51:41 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_single_fork(t_data *minish, t_list *token, int *pid, char *cmd_arg)
{
	if (*pid == KO)
	{
		minish->last_status = errno;
		return (ft_putstr_fd(FORK_ERR, STDERR_FILENO));
	}
	if (*pid == 0)
		child_single_fork(minish, token, cmd_arg);
}

void	child_single_fork(t_data *minish, t_list *token, char *cmd_arg)
{
	char	*path;
	char	**arg;

	arg = NULL;
	path = NULL;
	if (open_all_infile(minish) == KO || !cmd_arg || !cmd_arg[0]
		|| check_cmd_value(cmd_arg) == KO)
		exit(execve_error_free(minish, arg, path, token));
	path = split_n_path(minish, cmd_arg, &arg, token);
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
