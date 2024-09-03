/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 00:08:52 by phwang            #+#    #+#             */
/*   Updated: 2024/06/12 19:06:34 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	do_pipex(t_pipex *pipex, char **env)
{
	int	i;

	i = -1;
	open_pipe(pipex);
	while (++i < pipex->nb_cmds)
	{
		pipex->pid_tab[i] = fork();
		if (pipex->pid_tab[i] == ERROR)
			pipex_error(pipex);
		if (pipex->pid_tab[i] == 0)
			child_process(pipex, env, i);
	}
	close_fds_pipes(pipex);
	wait_child(pipex);
	free_all(pipex);
}

void	child_process(t_pipex *pipex, char **env, int cmd)
{
	if (cmd == 0)
	{
		if (pipex->fd_in == -1)
		{
			close_fds_pipes(pipex);
			free_all(pipex);
			exit(EXIT_FAILURE);
		}
		pipex_dup(pipex, pipex->fd_in, pipex->pipe_tab[cmd][WRITE]);
	}
	else if (cmd == pipex->nb_cmds - 1)
	{
		if (pipex->fd_out == -1)
		{
			close_fds_pipes(pipex);
			free_all(pipex);
			exit(EXIT_FAILURE);
		}
		pipex_dup(pipex, pipex->pipe_tab[cmd - 1][READ], pipex->fd_out);
	}
	else
		pipex_dup(pipex, pipex->pipe_tab[cmd - 1][READ],
			pipex->pipe_tab[cmd][WRITE]);
	close_fds_pipes(pipex);
	exit(execve_cmd(pipex, cmd, env));
}

void	pipex_dup(t_pipex *pipex, int in, int out)
{
	if (dup2(in, STDIN_FILENO) < 0 || dup2(out, STDOUT_FILENO) < 0)
		pipex_error(pipex);
}

int	execve_cmd(t_pipex *pipex, int cmd, char **env)
{
	char	**cmd_arg;

	cmd_arg = ft_split(pipex->cmds[cmd], ' ');
	if (!cmd_arg)
		return (return_err_msg(MALLOC_ERROR));
	if (execve(pipex->cmds_path[cmd], cmd_arg, env) < 0)
	{
		tab_free(cmd_arg);
		pipex_error(pipex);
	}
	tab_free(cmd_arg);
	return (EXIT_SUCCESS);
}
