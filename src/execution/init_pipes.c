/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:25:27 by phwang            #+#    #+#             */
/*   Updated: 2024/09/13 18:03:14 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipe(t_data *minishell)
{
	int	i;
	int	y;

	i = 0;
	while (minishell->command[i])
		i++;
	minishell->nb_cmd = i;
	minishell->pid_tab = ft_calloc(minishell->nb_cmd, sizeof(int));
	if (!minishell->pid_tab)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	minishell->pipe_fd = ft_calloc(minishell->nb_cmd - 1, sizeof(int *));
	if (!minishell->pipe_fd)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
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
		{
			y = -1;
			while (++y <= i)
				free(minishell->pipe_fd[y]);
			free(minishell->pipe_fd);
			perror(PIPE_ERR);
			minishell->last_status = errno;
			return (KO);
		}
	}
	return (OK);
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
			printf("pipe_fd[%d][WRITE] = %d\n", i,
				minishell->pipe_fd[i][WRITE]);
			minishell->last_status = errno;
		}
		if (close(minishell->pipe_fd[i][READ]) < 0)
		{
			perror(CLOSE_ERR);
			printf("pipe_fd[%d][READ] = %d\n", i, minishell->pipe_fd[i][READ]);
			minishell->last_status = errno;
		}
	}
}

void	wait_all_get_status(t_data *minishell)
{
	int	i;

	i = -1;
	while (++i < minishell->nb_cmd - 1)
		waitpid(minishell->pid_tab[i], 0, 0);
	get_status_process(minishell, &minishell->last_status,
		minishell->pid_tab[i]);
}
