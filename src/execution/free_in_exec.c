/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_in_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:20:31 by phwang            #+#    #+#             */
/*   Updated: 2024/09/18 15:22:54 by phwang           ###   ########.fr       */
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

void	execve_error(t_data *minishell, char *path, char **arg, t_list *token)
{
	execve_error_free(minishell, arg, path, token);
	perror(EXECVE_ERR);
	exit(errno);
}

int	execve_error_free(t_data *minish, char **arg, char *path, t_list *token)
{
	if (minish->command_tab[1])
	{
		close_all_pipes(minish);
		free_pipe_pid(minish);
	}
	if (minish->nb_files > 0)
		close_all_files(minish->files);
	free_files_tab(minish, minish->files);
	free_double_char(&minish->command_tab);
	free_double_char(&minish->cmd_original);
	free_double_char(&arg);
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
