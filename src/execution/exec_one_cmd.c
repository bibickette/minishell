/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:09:07 by phwang            #+#    #+#             */
/*   Updated: 2024/09/14 11:59:18 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_one_cmd(t_data *minish, char *cmd_arg, t_list *token)
{
	int		pid;
	char	**arg;

	if (!cmd_arg)
		return (OK);
	arg = ft_split(cmd_arg, ' ');
	if (is_builtin(arg[0]) == OK)
		handle_builtin(minish, arg, token);
	else
	{
		free_double_char(arg);
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
	if (redirection_out(minish, minish->files, STDOUT_FILENO) != OK)
	{
		minish->last_status = errno;
		close_all_files(minish->files);
		if (close(out) < 0)
		{
			perror(CLOSE_ERR);
			minish->last_status = errno;
		}
		return ;
	}
	ret = execve_builtin(minish, arg, token);
	if (minish->nb_files > 0)
		close_all_files(minish->files);
	minish->last_status = OK;
	if (ret == KO || ret == M_KO)
		minish->last_status = 1;
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
	free_double_char(arg);
}

void	do_single_fork(t_data *minish, t_list *token, int *pid, char *cmd_arg)
{
	char	*path;
	char	**arg;

	arg = NULL;
	path = NULL;
	if (*pid == KO)
	{
		minish->last_status = errno;
		return (ft_putstr_fd(FORK_ERR, STDERR_FILENO));
	}
	if (*pid == 0)
	{
		if(!cmd_arg[0])
		{
			execve_error_free(minish, arg, path, token);	
			exit(EXIT_FAILURE);
		}
		path = split_n_path(minish, cmd_arg, &arg, token);
		if (open_all_files(minish) == KO || redirection_in(minish,
				minish->files, STDIN_FILENO) != OK || redirection_out(minish,
				minish->files, STDOUT_FILENO) != OK)
		{
			execve_error_free(minish, arg, path, token);
			exit(EXIT_FAILURE);
		}
		if (minish->nb_files > 0)
			close_all_files(minish->files);
		if (execve(path, arg, minish->builtins->env) == KO)
			execve_error(minish, path, arg, token);
		exit(EXIT_SUCCESS);
	}
}

void	execve_error(t_data *minishell, char *path, char **arg, t_list *token)
{
	execve_error_free(minishell, arg, path, token);
	perror(EXECVE_ERR);
	exit(errno);
}

void	execve_error_free(t_data *minish, char **arg, char *path, t_list *token)
{
	if (minish->command[1])
	{
		close_all_pipes(minish);
		free_pipe_pid(minish);
	}
	if (minish->nb_files > 0)
		close_all_files(minish->files);
	free_files_tab(minish, minish->files);
	free_command_list(minish->command_list);
	free(minish->command);
	free_double_char(arg);
	ft_lstclear_custom(&token, free);
	ft_lstclear_custom(&minish->brut_list, free);
	if (path)
		free(path);
	apocalypse(minish);
}
