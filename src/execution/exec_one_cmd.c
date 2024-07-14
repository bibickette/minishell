/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:09:07 by phwang            #+#    #+#             */
/*   Updated: 2024/07/14 23:20:35 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_one_cmd(t_data *minishell, char *cmd_arg, int fd_dest)
{
	int		pid;
	char	**arg;
	char	*path;

	pid = fork();
	if (pid == KO)
		return (ft_putstr_fd(FORK_ERR, STDERR_FILENO), errno);
	if (pid == 0)
	{
		arg = ft_split(cmd_arg, ' ');
		if (dup2(fd_dest, STDOUT_FILENO) < 0)
			exit(errno);
		close_one_fd(fd_dest);
		path = find_path(arg[0], minishell->path);
		if (execve(path, arg, minishell->builtins->env) == KO)
		{
			close_one_fd(fd_dest);
			free_double_char(arg);
			perror(EXECVE_ERR);
			free(path);
			apocalypse(minishell);
			exit(errno);
		}
		exit(EXIT_SUCCESS);
	}
	close_one_fd(fd_dest);
	waitpid(pid, &minishell->last_status, 0);
	return (get_status_process(minishell, minishell->last_status));
}
/* still need to have the split + find_path malloc verification */

int	get_status_process(t_data *minishell, int status)
{
	minishell->last_status = WEXITSTATUS(status);
	if (minishell->last_status != 0)
		return (ft_putstr_fd(STATUS_ERR, STDERR_FILENO),
			minishell->last_status);
	return (minishell->last_status);
}

void	close_one_fd(int fd)
{
	if (fd != STDIN_FILENO && fd != STDOUT_FILENO && fd != STDERR_FILENO)
		close(fd);
}
