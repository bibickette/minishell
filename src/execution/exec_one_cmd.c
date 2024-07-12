/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:09:07 by phwang            #+#    #+#             */
/*   Updated: 2024/07/13 00:08:46 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_one_cmd(char *cmd_path, t_data *minishell, int fd_dest)
{
	int		pid;
	int		status;
	char	**arg;
	int		ret;

	arg = ft_split(cmd_path, ' ');
	pid = fork();
	if (pid < 0)
	{
		return (ft_putstr_fd(FORK_ERR, STDERR_FILENO), -1);
	}
	if (pid == 0)
	{
		if (dup2(fd_dest, STDOUT_FILENO) == -1)
			exit(errno);
		if (execve(cmd_path, arg, minishell->builtins->env) == -1)
		{
			close(fd_dest);
			exit(errno);
		}
		close(fd_dest);
		exit(EXIT_SUCCESS);
	}
	close(fd_dest);
	waitpid(pid, &status, 0);
	ret = WEXITSTATUS(status);
	if (ret != 0)
		return (ft_putstr_fd(STATUS_ERR, STDERR_FILENO), ret);
	return (ret);
}
