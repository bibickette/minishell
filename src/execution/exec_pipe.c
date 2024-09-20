/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:28:37 by phwang            #+#    #+#             */
/*   Updated: 2024/09/20 22:36:09 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

void	execve_pipe(t_data *minish, t_list *token)
{
	int		i;
	t_list	*cmd_head;

	cmd_head = minish->list_cmd;
	if (init_pipe(minish) == KO)
		return ;
	i = -1;
	g_signal = IN_PARENT;
	while (++i < minish->nb_cmd)
	{
		minish->pid_tab[i] = fork();
		if (minish->pid_tab[i] < 0)
		{
			perror(FORK_ERR);
			minish->last_status = errno;
			return ;
		}
		if (minish->pid_tab[i] == 0)
			child_process(minish, token, (t_cmd *)cmd_head->content);
		cmd_head = cmd_head->next;
	}
	close_all_pipes(minish);
	wait_all_get_status(minish);
	free_pipe_pid(minish);
}

void	child_process(t_data *minishell, t_list *token, t_cmd *cmd)
{
	char	*path;

	path = NULL;
	if (!cmd->cmd || !cmd->cmd[0] || check_cmd_value(cmd->cmd) == KO)
		exit(execve_error_free(minishell, path, token));
	do_the_dup(minishell, token, cmd);
	path = split_n_path(minishell, cmd, token);
	if (is_builtin(cmd->cmd) == OK)
	{
		execve_builtin(minishell, cmd);
		execve_error_free(minishell, path, token);
	}
	else
	{
		close_all_pipes(minishell);
		if (minishell->nb_hd_files > 0)
			close_all_files(minishell->files);
		if (cmd->nb_files > 0)
			close_all_files(cmd->files);
		if (execve(path, cmd->cmd_args, minishell->builtins->env) == KO)
			execve_error(minishell, path, token);
	}
	exit(EXIT_SUCCESS);
}
