/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:28:37 by phwang            #+#    #+#             */
/*   Updated: 2024/09/16 17:21:33 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_pipe(t_data *minish, char **cmd_tab, t_list *token)
{
	int	i;

	if (open_all_hd_file(minish) == KO || init_pipe(minish) == KO)
		return ;
	i = -1;
	while (++i < minish->nb_cmd)
	{
		minish->pid_tab[i] = fork();
		if (minish->pid_tab[i] < 0)
		{
			perror(FORK_ERR);
			minish->last_status = errno;
			return ;
		}
		if (minish->pid_tab[i] == 0)
			child_process(minish, cmd_tab, token, i);
	}
	close_all_pipes(minish);
	wait_all_get_status(minish);
	free_pipe_pid(minish);
}

void	child_process(t_data *minishell, char **cmd_tab, t_list *token, int cmd)
{
	char	**arg;
	char	*path;

	arg = NULL;
	path = NULL;
	if (!cmd_tab[cmd][0]
		|| check_cmd_value(cmd_tab[cmd]) == KO)
		exit(execve_error_free(minishell, arg, path, token));
	do_the_dup(minishell, token, cmd);
	path = split_n_path(minishell, cmd_tab[cmd], &arg, token);
	if (is_builtin(arg[0]) == OK)
	{
		execve_builtin(minishell, arg, token);
		execve_error_free(minishell, arg, path, token);
	}
	else
	{
		close_all_pipes(minishell);
		if (minishell->nb_files > 0)
			close_all_files(minishell->files);
		if (execve(path, arg, minishell->builtins->env) == KO)
			execve_error(minishell, path, arg, token);
	}
	exit(EXIT_SUCCESS);
}
