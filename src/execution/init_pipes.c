/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:25:27 by phwang            #+#    #+#             */
/*   Updated: 2024/09/19 01:59:06 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

int	init_pipe(t_data *minishell)
{
	minishell->pid_tab = ft_calloc(minishell->nb_cmd, sizeof(int));
	if (!minishell->pid_tab)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	minishell->pipe_fd = ft_calloc(minishell->nb_cmd - 1, sizeof(int *));
	if (!minishell->pipe_fd)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	if (open_pipe(minishell) == KO)
		return (KO);
	return (OK);
}

int	open_pipe(t_data *minishell)
{
	int	i;

	i = -1;
	while (++i < minishell->nb_cmd - 1)
	{
		minishell->pipe_fd[i] = ft_calloc(2, sizeof(int));
		if (!minishell->pipe_fd[i])
		{
			free(minishell->pipe_fd);
			return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
		}
		if (pipe(minishell->pipe_fd[i]) < 0)
			if (error_open_pipe(minishell, i) == KO)
				return (KO);
	}
	return (OK);
}

int	error_open_pipe(t_data *minishell, int i)
{
	int	y;

	y = -1;
	while (++y <= i)
	{
		free(minishell->pipe_fd[y]);
		minishell->pipe_fd[y] = 0;
	}
	free(minishell->pipe_fd);
	minishell->pipe_fd = 0;
	free(minishell->pid_tab);
	minishell->pid_tab = 0;
	perror(PIPE_ERR);
	minishell->last_status = errno;
	return (KO);
}

void	close_all_pipes(t_data *minishell)
{
	int	i;

	i = -1;
	while (++i < minishell->nb_cmd - 1)
	{
		if (close(minishell->pipe_fd[i][WRITE]) < 0)
		{
			perror(CLOSE_ERR);
			minishell->last_status = errno;
		}
		if (close(minishell->pipe_fd[i][READ]) < 0)
		{
			perror(CLOSE_ERR);
			minishell->last_status = errno;
		}
	}
}

void	wait_all_get_status(t_data *minishell)
{
	int	i;

	i = -1;
	get_status_process(minishell, &minishell->last_status,
		minishell->pid_tab[minishell->nb_cmd - 1]);
	while (++i < minishell->nb_cmd - 1)
	{
		handle_signals(minishell);
		waitpid(minishell->pid_tab[i], 0, 0);
	}
	g_signal = 0;
}
