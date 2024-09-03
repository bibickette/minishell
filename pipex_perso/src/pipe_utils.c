/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 19:03:58 by phwang            #+#    #+#             */
/*   Updated: 2024/06/06 19:31:37 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	pipex_error(t_pipex *pipex)
{
	perror(PERR_MSG);
	close_fds_pipes(pipex);
	free_all(pipex);
	exit(errno);
}

void	open_pipe(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->nb_cmds - 1)
		if (pipe(pipex->pipe_tab[i]) == ERROR)
			pipex_error(pipex);
}

void	close_fds_pipes(t_pipex *pipex)
{
	int	i;

	i = -1;
	if (pipex->fd_in != -1)
		close(pipex->fd_in);
	if (pipex->fd_out != -1)
		close(pipex->fd_out);
	while (++i < pipex->nb_cmds - 1)
	{
		close(pipex->pipe_tab[i][WRITE]);
		close(pipex->pipe_tab[i][READ]);
	}
}

void	wait_child(t_pipex *pipex)
{
	int	i;

	i = -1;
	while (++i < pipex->nb_cmds)
		waitpid(pipex->pid_tab[i], 0, 0);
}
