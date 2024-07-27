/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:09:07 by phwang            #+#    #+#             */
/*   Updated: 2024/07/27 23:11:58 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_one_cmd(t_data *minish, char *cmd_arg, int fd_dest)
{
	int		pid;
	char	**arg;
	char	*path;

	arg = NULL;
	path = NULL;
	pid = fork();
	if (pid == KO)
		return (ft_putstr_fd(FORK_ERR, STDERR_FILENO), errno);
	if (pid == 0)
	{
		split_n_path(minish, cmd_arg, &arg, &path);
		if (redirection_dup(STDIN_FILENO, fd_dest) != OK)
		{
			free_double_char(arg);
			free(path);
			apocalypse(minish);
			exit(errno);
		}
		close_one_fd(fd_dest);
		if (execve(path, arg, minish->builtins->env) == KO)
			execve_error(minish, path, arg, fd_dest);
		exit(EXIT_SUCCESS);
	}
	return (get_status_process(minish, minish->last_status, pid, fd_dest));
}

void	close_one_fd(int fd)
{
	if (fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
		close(fd);
}

void	split_n_path(t_data *minishell, char *cmd_arg, char ***arg, char **path)
{
	*arg = ft_split(cmd_arg, ' ');
	if (!arg)
	{
		ft_putstr_fd(SPLIT_ERR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	*path = find_path(*arg[0], minishell->path);
	if (!*path)
	{
		ft_putstr_fd(CMD_NOT_FOUND, STDERR_FILENO);
		if (cmd_arg)
			free(cmd_arg);
		free_double_char(*arg);
		apocalypse(minishell);
		exit(EXIT_FAILURE);
	}
}

void	execve_error(t_data *minishell, char *path, char **arg, int fd_dest)
{
	close_one_fd(fd_dest);
	free_double_char(arg);
	perror(EXECVE_ERR);
	if (path)
		free(path);
	apocalypse(minishell);
	exit(errno);
}

int	get_status_process(t_data *minishell, int status, pid_t pid, int fd_dest)
{
	close_one_fd(fd_dest);
	waitpid(pid, &minishell->last_status, 0);
	minishell->last_status = WEXITSTATUS(status);
	if (minishell->last_status != 0)
		return (ft_putstr_fd(STATUS_ERR, STDERR_FILENO),
			minishell->last_status);
	return (minishell->last_status);
}
