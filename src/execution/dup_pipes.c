/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:08:53 by phwang            #+#    #+#             */
/*   Updated: 2024/09/23 22:41:36 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_the_dup(t_data *minishell, t_list *token, t_cmd *cmd)
{
	char	*path;

	path = NULL;
	if (cmd->index == 0)
		dup_first_cmd(minishell, token, cmd);
	else if (cmd->index == minishell->nb_cmd - 1)
		dup_last_cmd(minishell, token, cmd);
	else
	{
		// ft_putstr_fd("GROS CACA\n", STDERR_FILENO);
		// printf("GROS CACA\n");
		if (has_infile(minishell, cmd) == OK)
		{
			if (open_all_infile(minishell, cmd) == KO
				|| redirection_in(minishell, minishell->files, cmd,
					STDIN_FILENO) != OK)
				exit(execve_error_free(minishell, path, token));
			// close(minishell->pipe_fd[cmd->index - 1][READ]);
		}
		else
			dup2(minishell->pipe_fd[cmd->index - 1][READ], STDIN_FILENO);
		// else
		// if (open_all_outfile(minishell, cmd) == KO || redirection_out(cmd,
		// 		cmd->files, STDOUT_FILENO) != OK)
		// 	exit(execve_error_free(minishell, path, token));
		// if(has_infile(minishell, get_cmd_by_index(minishell,cmd->index
		// + 1)) == KO)
		if (has_outfile(cmd) == OK)
		{
			if (open_all_outfile(minishell, cmd) == KO || redirection_out(cmd,
					cmd->files, STDOUT_FILENO) != OK)
				exit(execve_error_free(minishell, path, token));
			close_all_files(cmd->files);
		}
		else
			dup2(minishell->pipe_fd[cmd->index][WRITE], STDOUT_FILENO);
		// else
		// if (dup2(minishell->pipe_fd[cmd->index - 1][READ],
		// STDIN_FILENO) < 0
		// 	|| dup2(minishell->pipe_fd[cmd->index][WRITE],
		// STDOUT_FILENO) < 0)
		// {
		// 	perror(DUP_ERR);
		// 	execve_error_free(minishell, path, token);
		// 	exit(errno);
		// }
	}
}

t_cmd	*get_cmd_by_index(t_data *minishell, int index)
{
	t_list	*tmp;

	tmp = minishell->list_cmd;
	while (tmp)
	{
		if (((t_cmd *)tmp->content)->index == index)
			return ((t_cmd *)tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

void	dup_first_cmd(t_data *minishell, t_list *token, t_cmd *cmd)
{
	char	*path;

	// t_cmd	*next_cmd;
	// next_cmd = (t_cmd *)minishell->list_cmd->next->content;
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
	// }
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

int	has_infile(t_data *minishell, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < minishell->nb_hd_files)
	{
		if (minishell->files[i].index_cmd == cmd->index)
			return (OK);
	}
	i = -1;
	while (++i < cmd->nb_files)
		if (cmd->files[i].type == INFILE_TYPE)
			return (OK);
	return (KO);
}

int	has_outfile(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->nb_files)
		if (cmd->files[i].type == OUTFILE_TYPE
			|| cmd->files[i].type == APPEND_FILE_TYPE)
			return (OK);
	return (KO);
}
