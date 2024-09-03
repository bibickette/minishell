/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:26:33 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/03 16:50:19 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
static int	exec_redirect(int (*exec_one_cmd_redirect)(t_data, char *, int ), \
				t_data *minishell, char *cmd_arg, char *output)
{
	int	ret;
	int	fd;

	fd = 0;
	fd = get_fd(ouput);
	exec_one_cmd_redirect(minishell, );
}

void	execution(t_data *minishell)
{
	t_command	*command;

	command = (t_command *)minishell->command_list->content;
	if (command->output)
		exec_redirect(execve_one_cmd, minishell, command, command->output);
	else
		execve_one_cmd(minishell, (char *)command->entire_command, 1);
	if (fd != 0)
		close(fd);
}
*/
