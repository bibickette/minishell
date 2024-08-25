/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:13:30 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/25 13:55:51 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_command(t_command *command)
{
	int	i;

	if (!command)
		return ;
	if (command->command)
		free(command->command);
	if (command->option)
	{
		i = 0;
		while (command->option[i])
		{
			free(command->option[i]);
			i++;
		}
		free(command->option);
	}
	if (command->arg)
	{
		i = 0;
		while (command->arg[i])
		{
			free(command->arg[i]);
			i++;
		}
		free(command->arg);
	}
	if (command->output)
		free(command->output);
	if (command->redirection)
		free(command->redirection);
	free(command);
}

void	free_command_list(t_list *command_list)
{
	t_list	*tmp;

	while (command_list)
	{
		tmp = command_list->next;
		free_command((t_command *)command_list->content);
		free(command_list);
		command_list = tmp;
	}
}
