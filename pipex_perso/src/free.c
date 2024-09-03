/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:21:46 by phwang            #+#    #+#             */
/*   Updated: 2024/06/12 19:14:06 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	exit_error(t_pipex *pipex, char *error_msg)
{
	ft_putstr_fd(error_msg, STDERR_FILENO);
	free_all(pipex);
	exit(EXIT_FAILURE);
}

int	return_err_msg(char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	return (ERROR);
}

void	free_all(t_pipex *pipex)
{
	int	i;

	if (pipex->path)
		tab_free(pipex->path);
	if (pipex->cmds)
		tab_free(pipex->cmds);
	if (pipex->cmds_path)
		tab_free(pipex->cmds_path);
	if (pipex->pid_tab)
		free(pipex->pid_tab);
	if (pipex->pipe_tab)
	{
		i = -1;
		while (++i < pipex->nb_cmds - 1)
			if (pipex->pipe_tab[i])
				free(pipex->pipe_tab[i]);
		free(pipex->pipe_tab);
	}
}

void	tab_free(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	while (len >= 0)
	{
		if (tab[len])
			free(tab[len]);
		len--;
	}
	free(tab);
	tab = 0;
}
