/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:08:53 by phwang            #+#    #+#             */
/*   Updated: 2024/09/20 19:25:06 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	do_the_dup(t_data *minishell, t_list *token, int cmd)
// {
// 	char	*path;

// 	path = NULL;
// 	if (cmd == 0)
// 		dup_first_cmd(minishell, token);
// 	else if (cmd == minishell->nb_cmd - 1)
// 		dup_last_cmd(minishell, token, cmd);
// 	else
// 	{
// 		if (dup2(minishell->pipe_fd[cmd - 1][READ], STDIN_FILENO) < 0
// 			|| dup2(minishell->pipe_fd[cmd][WRITE], STDOUT_FILENO) < 0)
// 		{
// 			perror(DUP_ERR);
// 			execve_error_free(minishell, path, token);
// 			exit(errno);
// 		}
// 	}
// }

// void	dup_first_cmd(t_data *minishell, t_list *token)
// {
// 	char	**arg;
// 	char	*path;

// 	arg = NULL;
// 	path = NULL;
// 	if (open_all_infile(minishell) == KO || redirection_in(minishell,
// 			minishell->files, cmd, STDIN_FILENO) != OK)
// 		exit(execve_error_free(minishell, arg, path, token));
// 	if (dup2(minishell->pipe_fd[0][WRITE], STDOUT_FILENO) < 0)
// 	{
// 		perror(DUP_ERR);
// 		execve_error_free(minishell, arg, path, token);
// 		exit(errno);
// 	}
// }

// void	dup_last_cmd(t_data *minishell, t_list *token, int cmd)
// {
// 	char	**arg;
// 	char	*path;

// 	arg = NULL;
// 	path = NULL;
// 	if (open_all_outfile(minishell) == KO || redirection_out(minishell,
// 			minishell->files, STDOUT_FILENO) != OK)
// 		exit(execve_error_free(minishell, arg, path, token));
// 	if (dup2(minishell->pipe_fd[cmd - 1][READ], STDIN_FILENO) < 0)
// 	{
// 		perror(DUP_ERR);
// 		execve_error_free(minishell, arg, path, token);
// 		exit(errno);
// 	}
// }
