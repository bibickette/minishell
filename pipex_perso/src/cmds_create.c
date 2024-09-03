/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_create.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 23:21:46 by phwang            #+#    #+#             */
/*   Updated: 2024/06/17 17:07:11 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	cpy_path_cmd(t_pipex *pipex, char *path_cmd, int cmd)
{
	pipex->cmds_path[cmd] = ft_strdup(path_cmd);
	free(path_cmd);
	if (!pipex->cmds_path[cmd])
		return (return_err_msg(MALLOC_ERROR));
	return (OK);
}

int	create_cmd(t_pipex *pipex, int argc, char **argv)
{
	int	i;

	i = -1;
	pipex->cmds = ft_calloc((argc - 2), sizeof(char *));
	if (!pipex->cmds)
		return (return_err_msg(MALLOC_ERROR));
	while (++i + 3 < argc)
	{
		pipex->cmds[i] = ft_strdup(argv[2 + i]);
		if (!pipex->cmds[i])
			return (return_err_msg(MALLOC_ERROR));
	}
	pipex->cmds[i] = 0;
	pipex->nb_cmds = i;
	return (pid_pipe_tab_create(pipex));
}

int	create_cmd_path(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (pipex->cmds[i])
		i++;
	pipex->cmds_path = ft_calloc((i + 1), sizeof(char *));
	if (!pipex->cmds_path)
		return (return_err_msg(MALLOC_ERROR));
	pipex->cmds_path[i] = 0;
	return (OK);
}

int	pid_pipe_tab_create(t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->pid_tab = ft_calloc(pipex->nb_cmds, sizeof(pid_t));
	if (!pipex->pid_tab)
		return (return_err_msg(MALLOC_ERROR));
	pipex->pipe_tab = ft_calloc((pipex->nb_cmds - 1), sizeof(int *));
	if (!pipex->pipe_tab)
		return (return_err_msg(MALLOC_ERROR));
	while (++i < pipex->nb_cmds - 1)
	{
		pipex->pipe_tab[i] = ft_calloc(2, sizeof(int));
		if (!pipex->pipe_tab[i])
			return (return_err_msg(MALLOC_ERROR));
	}
	return (OK);
}
