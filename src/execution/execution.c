/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:26:33 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/02 19:53:22 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_data *minishell)
{
	t_command	*command;
	int		fd;

	fd = 0;
	command = (t_command *)minishell->command_list->content;
	if (command->output)
	{
		fd = get_fd(command->output);
		execve_one_cmd(minishell, (char *)command->entire_command, fd);
	}
	else
		execve_one_cmd(minishell, (char *)command->entire_command, 1);
	if (fd != 0)
		close(fd);
}
