/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:09:07 by phwang            #+#    #+#             */
/*   Updated: 2024/09/24 21:59:41 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

int	execve_one_cmd(t_data *minish, t_list *token)
{
	int		pid;
	t_cmd	*cmd;

	cmd = (t_cmd *)minish->list_cmd->content;
	if (!cmd->cmd)
		return (OK);
	if (is_builtin(cmd->cmd) == OK)
		handle_builtin(minish, token);
	else
	{
		g_signal = IN_PARENT;
		pid = fork();
		do_single_fork(minish, token, cmd, &pid);
		return (get_status_process(minish, &minish->last_status, pid));
	}
	return (OK);
}

void	handle_builtin(t_data *minish, t_list *token)
{
	int	ret;
	int	out;

	if (ft_strcmp(((t_cmd *)minish->list_cmd->content)->cmd, "exit") == 0)
		exit_cmd(token, ((t_cmd *)minish->list_cmd->content), minish);
	out = dup(STDOUT_FILENO);
	if (out < 0)
	{
		perror(DUP_SIMPLE_ERR);
		minish->last_status = errno;
		return ;
	}
	if (do_redir_builtin_one_cmd(minish, out) == KO)
		return ;
	ret = execve_builtin(minish, (t_cmd *)minish->list_cmd->content);
	if (((t_cmd *)minish->list_cmd->content)->nb_files > 0)
		close_all_files(((t_cmd *)minish->list_cmd->content)->files);
	minish->last_status = 0;
	if (ret == KO || ret == M_KO)
		minish->last_status = 1;
	put_back_in_term_n_close(minish, out);
}

int	do_redir_builtin_one_cmd(t_data *minish, int out)
{
	if (open_all_outfile(minish, (t_cmd *)minish->list_cmd->content) == KO
		|| redirection_out(((t_cmd *)minish->list_cmd->content),
			((t_cmd *)minish->list_cmd->content)->files, STDOUT_FILENO) != OK)
	{
		minish->last_status = errno;
		close_all_files(((t_cmd *)minish->list_cmd->content)->files);
		if (close(out) < 0)
		{
			perror(CLOSE_ERR);
			minish->last_status = errno;
		}
		return (KO);
	}
	return (OK);
}

void	put_back_in_term_n_close(t_data *minish, int out)
{
	if (dup2(out, STDOUT_FILENO) < 0)
	{
		perror(DUP_ERR);
		minish->last_status = errno;
	}
	if (close(out) < 0)
	{
		perror(CLOSE_ERR);
		minish->last_status = errno;
	}
}
