/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:28:37 by phwang            #+#    #+#             */
/*   Updated: 2024/09/13 18:43:34 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_pipe(t_data *minish, t_list *token)
{
	int	i;

	if (init_pipe(minish) == KO)
		return ;
	i = -1;
	open_all_files(minish);
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
			child_process(minish, token, i);
	}
	close_all_pipes(minish);
	wait_all_get_status(minish);
	free_pipe_pid(minish);
}

void	child_process(t_data *minishell, t_list *token, int cmd)
{
	char	**arg;
	char	*path;

	path = split_n_path(minishell, minishell->command[cmd], &arg, token);
	if (cmd == 0)
	{
		if (redirection_in(minishell, minishell->files, STDIN_FILENO) != OK)
			execve_error_free(minishell, arg, path, token);
		if (dup2(minishell->pipe_fd[0][WRITE], STDOUT_FILENO) < 0)
		{
			perror(DUP_ERR);
			execve_error_free(minishell, arg, path, token);
			exit(errno);
		}
	}
	else if (cmd == minishell->nb_cmd - 1)
	{
		if (dup2(minishell->pipe_fd[cmd - 1][READ], STDIN_FILENO) < 0)
		{
			perror(DUP_ERR);
			execve_error_free(minishell, arg, path, token);
			exit(errno);
		}
		if (redirection_out(minishell, minishell->files, STDOUT_FILENO) != OK)
		{
			execve_error_free(minishell, arg, path, token);
			exit(errno);
		}
	}
	else
	{
		if (dup2(minishell->pipe_fd[cmd - 1][READ], STDIN_FILENO) < 0
			|| dup2(minishell->pipe_fd[cmd][WRITE], STDOUT_FILENO) < 0)
		{
			perror(DUP_ERR);
			execve_error_free(minishell, arg, path, token);
			exit(errno);
		}
	}
	if (is_builtin(arg[0]) == OK)
	{
		execve_builtin(minishell, arg, token);
		execve_error_free(minishell, arg, path, token);
	}
	else
	{
		close_all_pipes(minishell);
		if (minishell->nb_files > 0)
			close_all_files(minishell->files);
		if (execve(path, arg, minishell->builtins->env) == KO)
			execve_error(minishell, path, arg, token);
	}
	exit(EXIT_SUCCESS);
}

void	free_pipe_pid(t_data *minishell)
{
	int	i;

	i = -1;
	free(minishell->pid_tab);
	while (++i < minishell->nb_cmd - 1)
		free(minishell->pipe_fd[i]);
	free(minishell->pipe_fd);
}
