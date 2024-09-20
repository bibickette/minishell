/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:09:07 by phwang            #+#    #+#             */
/*   Updated: 2024/09/20 19:43:33 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_one_cmd(t_data *minish, t_list *token)
{
	int		pid;
	t_list	*cmd_list;

	cmd_list = minish->list_cmd;
	if (is_builtin(((t_cmd *)cmd_list->content)->cmd) == OK)
		handle_builtin(minish);
	else
	{
		pid = fork();
		do_single_fork(minish, token, (t_cmd *)cmd_list->content, &pid);
		return (get_status_process(minish, &minish->last_status, pid));
	}
	return (OK);
}

void	handle_builtin(t_data *minish)
{
	int	ret;
	int	out;

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
	minish->last_status = OK;
	if (ret == KO || ret == M_KO)
		minish->last_status = 1;
	put_back_in_term_n_close(minish, out);
}

int	do_redir_builtin_one_cmd(t_data *minish, int out)
{
	if (open_all_outfile(minish, (t_cmd *)minish->list_cmd->content) == KO
		|| redirection_out(((t_cmd *)minish->list_cmd->content), \
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
