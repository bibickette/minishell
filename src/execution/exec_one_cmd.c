/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:09:07 by phwang            #+#    #+#             */
/*   Updated: 2024/09/16 17:25:07 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_one_cmd(t_data *minish, char *cmd_arg, t_list *token)
{
	int		pid;
	char	**arg;

	arg = ft_split(cmd_arg, ' ');
	if (is_builtin(arg[0]) == OK)
		handle_builtin(minish, arg, token);
	else
	{
		free_double_char(&arg);
		pid = fork();
		do_single_fork(minish, token, &pid, cmd_arg);
		return (get_status_process(minish, &minish->last_status, pid));
	}
	return (OK);
}

void	handle_builtin(t_data *minish, char **arg, t_list *token)
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
	ret = execve_builtin(minish, arg, token);
	if (minish->nb_files > 0)
		close_all_files(minish->files);
	minish->last_status = OK;
	if (ret == KO || ret == M_KO)
		minish->last_status = 1;
	put_back_in_term_n_close(minish, out);
	free_double_char(&arg);
}

int	do_redir_builtin_one_cmd(t_data *minish, int out)
{
	if (open_all_outfile(minish) == KO || redirection_out(minish, minish->files,
			STDOUT_FILENO) != OK)
	{
		minish->last_status = errno;
		close_all_files(minish->files);
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
