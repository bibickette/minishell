/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:26:33 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/02 19:05:28 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_data *minishell)
{
	t_command	*command;

	command = (t_command *)minishell->command_list->content;
	printf("execution launch\n");
	execve_one_cmd(minishell, (char *)command->entire_command, 1);
}
