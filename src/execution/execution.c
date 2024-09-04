/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:26:33 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/04 17:15:43 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static int	exec_redirect_ouput(int (*exec_one_cmd_redirect)(t_data *, char *, int ), \
				t_data *minishell, t_command *command)
{
	int	ret;
	int	fd;

	fd = 0;
	fd = get_fd(command->output);
	ret = exec_one_cmd_redirect(minishell, command->entire_command, fd);
	printf("ret = %d\n", ret);
	if (fd >= 0)
		close(fd);
	return (ret);
}

static int	exec_redirect_input(int (*exec_one_cmd_redirect)(t_data *, char *, int ), \
				t_data *minishell, t_command *command)
{
	int	ret;
	int	fd;

	fd = 0;
	fd = get_fd(command->input);
	ret = exec_one_cmd_redirect(minishell, command->entire_command, fd);
	if (fd >= 0)
		close(fd);
	return (ret);
}

void	execution(t_data *minishell)
{
	t_command	*command;

	command = (t_command *)minishell->command_list->content;
	if (command->output)
		exec_redirect_output(execve_one_cmd, minishell, command);
	else
		execve_one_cmd(minishell, (char *)command->entire_command, 1);
}
*/
