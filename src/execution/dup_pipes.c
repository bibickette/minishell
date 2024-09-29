/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:08:53 by phwang            #+#    #+#             */
/*   Updated: 2024/09/29 21:59:56 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_the_dup(t_data *minishell, t_list *token, t_cmd *cmd)
{
	char	*path;

	path = NULL;
	if (cmd->index == 0)
		return (dup_first_cmd(minishell, token, cmd));
	else if (cmd->index == minishell->nb_cmd - 1)
		return (dup_last_cmd(minishell, token, cmd));
	if (has_infile(minishell, cmd) == OK)
	{
		if (open_all_infile(minishell, cmd) == KO || redirection_in(minishell,
				minishell->files, cmd, STDIN_FILENO) != OK)
			exit(execve_error_free(minishell, path, token));
	}
	else
		dup2(minishell->pipe_fd[cmd->index - 1][READ], STDIN_FILENO);
	if (has_outfile(cmd) == OK)
	{
		if (open_all_outfile(minishell, cmd) == KO || redirection_out(cmd,
				cmd->files, STDOUT_FILENO) != OK)
			exit(execve_error_free(minishell, path, token));
		close_all_files(cmd->files);
	}
	else
		dup2(minishell->pipe_fd[cmd->index][WRITE], STDOUT_FILENO);
}

void	dup_first_cmd(t_data *minishell, t_list *token, t_cmd *cmd)
{
	char	*path;

	path = NULL;
	if (open_all_infile(minishell, cmd) == KO || redirection_in(minishell,
			minishell->files, cmd, STDIN_FILENO) != OK)
		exit(execve_error_free(minishell, path, token));
	if (has_outfile(cmd) == OK)
	{
		if (open_all_outfile(minishell, cmd) == KO || redirection_out(cmd,
				cmd->files, STDOUT_FILENO) != OK)
			exit(execve_error_free(minishell, path, token));
		close_all_files(cmd->files);
	}
	else
	{
		if (dup2(minishell->pipe_fd[0][WRITE], STDOUT_FILENO) < 0)
		{
			perror(DUP_ERR);
			execve_error_free(minishell, path, token);
			exit(errno);
		}
	}
}

void	dup_last_cmd(t_data *minishell, t_list *token, t_cmd *cmd)
{
	char	*path;

	path = NULL;
	if (has_infile(minishell, cmd) == OK)
	{
		if (open_all_infile(minishell, cmd) == KO || redirection_in(minishell,
				minishell->files, cmd, STDIN_FILENO) != OK)
			exit(execve_error_free(minishell, path, token));
	}
	else
	{
		if (dup2(minishell->pipe_fd[cmd->index - 1][READ], STDIN_FILENO) < 0)
		{
			perror(DUP_ERR);
			execve_error_free(minishell, path, token);
			exit(errno);
		}
	}
	if (open_all_outfile(minishell, cmd) == KO || redirection_out(cmd,
			cmd->files, STDOUT_FILENO) != OK)
		exit(execve_error_free(minishell, path, token));
	close_all_files(cmd->files);
}
