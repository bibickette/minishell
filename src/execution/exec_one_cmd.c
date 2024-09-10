/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:09:07 by phwang            #+#    #+#             */
/*   Updated: 2024/09/10 23:43:23 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_one_cmd(t_data *minish, char *cmd_arg, t_list *token)
{
	int		pid;
	char	**arg;

	arg = ft_split(cmd_arg, ' ');
	if (is_builtin(arg[0]) == OK)
		handle_builtin(minish, arg, token);
	else
	{
		free_double_char(arg);
		pid = fork();
		do_single_fork(minish, token, &pid, cmd_arg);
		return (get_status_process(minish, &minish->last_status, pid));
	}
	return (OK);
}

void	handle_builtin(t_data *minish, char **arg, t_list *token)
{
	int	ret;
	int std_in;
	int std_out;

	std_in = dup(STDIN_FILENO);
	std_out = dup(STDOUT_FILENO);
	// dup2(STDOUT_FILENO, std_out);
	// std_out = STDOUT_FILENO;
	printf("std_in : %d\n", std_in);
	printf("std_out : %d\n", std_out);
	if (redirection_in(minish, minish->files) != OK || redirection_out(minish,
			minish->files, STDOUT_FILENO) != OK)
		minish->last_status = 1;
	else
	{
		ret = execve_builtin(minish, arg, token);
		if(minish->nb_files > 0)
			close_all_files(minish->files);
		minish->last_status = OK;
		if (ret == KO || ret == M_KO)
			minish->last_status = 1;
	}
	// close(STDOUT_FILENO);
	// close(STDIN_FILENO);
	dup2(std_in, STDIN_FILENO);
	dup2(std_out, STDOUT_FILENO);
	// open("/dev/pts/0", O_RDONLY);
	close(std_in);
	close(std_out);
	free_double_char(arg);
}

void	do_single_fork(t_data *minish, t_list *token, int *pid, char *cmd_arg)
{
	char	*path;
	char	**arg;

	arg = NULL;
	path = NULL;
	if (*pid == KO)
	{
		minish->last_status = errno;
		return (ft_putstr_fd(FORK_ERR, STDERR_FILENO));
	}
	if (*pid == 0)
	{
		path = split_n_path(minish, cmd_arg, &arg, token);
		if (redirection_in(minish, minish->files) != OK
			|| redirection_out(minish, minish->files, STDOUT_FILENO) != OK)
		{
			exceve_error_free(minish, arg, path, token);
			exit(EXIT_FAILURE);
		}
		if (minish->nb_files > 0)
			close_all_files(minish->files);
		if (execve(path, arg, minish->builtins->env) == KO)
			execve_error(minish, path, arg, token);
		exit(EXIT_SUCCESS);
	}
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
	if (is_builtin((*arg)[0]) == OK)
		path = ft_strdup((*arg)[0]);
	else
		path = find_path(*arg[0], minishell->path);
	if (!path)
	{
		ft_putstr_fd(CMD_NOT_FOUND, STDERR_FILENO);
		exceve_error_free(minishell, *arg, path, token);
		exit(127);
	}
	return (path);
}

void	execve_error(t_data *minishell, char *path, char **arg, t_list *token)
{
	exceve_error_free(minishell, arg, path, token);
	perror(EXECVE_ERR);
	exit(126);
}

int	get_status_process(t_data *minishell, int *status, pid_t pid)
{
	if (minishell->nb_files > 0)
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
	if (path)
		free(path);
	apocalypse(minish);
}
