/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_in_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:20:31 by phwang            #+#    #+#             */
/*   Updated: 2024/09/20 19:43:52 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipe_pid(t_data *minishell)
{
	int	i;

	i = -1;
	free(minishell->pid_tab);
	minishell->pid_tab = 0;
	while (++i < minishell->nb_cmd - 1)
	{
		free(minishell->pipe_fd[i]);
		minishell->pipe_fd[i] = 0;
	}
	free(minishell->pipe_fd);
	minishell->pipe_fd = 0;
}

void	execve_error(t_data *minishell, char *path, t_list *token)
{
	execve_error_free(minishell, path, token);
	perror(EXECVE_ERR);
	exit(errno);
}

int	execve_error_free(t_data *minish, char *path, t_list *token)
{
	if (minish->nb_cmd > 1)
	{
		close_all_pipes(minish);
		free_pipe_pid(minish);
	}
	if (minish->nb_hd_files > 0)
		close_all_files(minish->files);
	free_files_tab(minish, minish->files);
	ft_lstclear_custom_cmd(&minish->list_cmd, free);
	ft_lstclear_custom(&token, free);
	ft_lstclear_custom(&minish->brut_list, free);
	if (path)
	{
		free(path);
		path = 0;
	}
	apocalypse(minish);
	return (EXIT_FAILURE);
}

int	check_cmd_value(char *str)
{
	size_t	i;

	i = -1;
	while (++i < ft_strlen(str))
	{
		if (str[i] != ' ')
			return (OK);
	}
	return (KO);
}
