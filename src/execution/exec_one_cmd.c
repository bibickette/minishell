/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:09:07 by phwang            #+#    #+#             */
/*   Updated: 2024/09/06 13:38:00 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_one_cmd(t_data *minish, char *cmd_arg, t_list *token)
{
	int		pid;
	char	**arg;
	char	*path;

	arg = NULL;
	path = NULL;
	pid = fork();
	if (pid == KO)
		return (ft_putstr_fd(FORK_ERR, STDERR_FILENO), errno);
	if (pid == 0)
	{
		path = split_n_path(minish, cmd_arg, &arg, token);
		if (redirection_in(minish, minish->files) != OK
			|| redirection_out(minish, minish->files) != OK)
		{
			exceve_error_free(minish, arg, path, token);
			exit(EXIT_FAILURE);
		}
		close_all_files(minish->files);
		if (execve(path, arg, minish->builtins->env) == KO)
			execve_error(minish, path, arg);
		exit(EXIT_SUCCESS);
	}
	return (get_status_process(minish, &minish->last_status, pid));
}

char	*split_n_path(t_data *minishell, char *cmd_arg, char ***arg,
		t_list *token)
{
	char	*path;

	*arg = ft_split(cmd_arg, ' ');
	if (!arg)
	{
		ft_putstr_fd(SPLIT_ERR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	path = find_path(*arg[0], minishell->path);
	if (!path)
	{
		ft_putstr_fd(CMD_NOT_FOUND, STDERR_FILENO);
		exceve_error_free(minishell, *arg, path, token);
		exit(127);
	}
	return (path);
}

void	execve_error(t_data *minishell, char *path, char **arg)
{
	exceve_error_free(minishell, arg, path, minishell->brut_list);
	perror(EXECVE_ERR);
	exit(126);
}

int	get_status_process(t_data *minishell, int *status, pid_t pid)
{
	close_all_files(minishell->files);
	waitpid(pid, &minishell->last_status, 0);
	minishell->last_status = WEXITSTATUS(*status);
	if (minishell->last_status != 0 && minishell->last_status != 127
		&& minishell->last_status != 126
		&& minishell->last_status != EXIT_FAILURE)
		return (ft_putstr_fd(STATUS_ERR, STDERR_FILENO),
			minishell->last_status);
	return (minishell->last_status);
}

void	exceve_error_free(t_data *minish, char **arg, char *path, t_list *token)
{
	close_all_files(minish->files);
	free_files_tab(minish, minish->files);
	free_command_list(minish->command_list);
	free_double_char(arg);
	ft_lstclear_custom(&token, free);
	ft_lstclear_custom(&minish->brut_list, free);
	free(path);
	apocalypse(minish);
}
