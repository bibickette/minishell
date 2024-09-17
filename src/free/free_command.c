/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:39:59 by phwang            #+#    #+#             */
/*   Updated: 2024/09/14 16:20:40 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_command(t_command *command)
// {
// 	if (!command)
// 		return ;
// 	if (command->command)
// 		free(command->command);
// 	command->command = NULL;
// 	if (command->option)
// 		free_double_char(&(command->option));
// 	command->option = NULL;
// 	if (command->arg)
// 		free_double_char(&(command->arg));
// 	command->arg = NULL;
// 	if (command->outputs)
// 		free_double_char(&(command->outputs));
// 	command->outputs = NULL;
// 	if (command->redirections)
// 		free_double_char(&(command->redirections));
// 	command->redirections = NULL;
// 	if (command->inputs)
// 		free_double_char(&(command->inputs));
// 	command->inputs = NULL;
// 	if (command->entire_command)
// 		free(command->entire_command);
// 	command->entire_command = NULL;
// 	free(command);
// 	command = NULL;
// }

// void	free_command_list(t_list *command_list, t_data *minishell)
// {
// 	t_list	*tmp;

// 	while (command_list)
// 	{
// 		tmp = command_list->next;
// 		if (command_list->content)
// 		{
// 			free_command((t_command *)command_list->content);
// 			command_list->content = NULL;
// 		}
// 		free(command_list);
// 		command_list = tmp;
// 	}
// 	if (minishell->command)
// 	{
// 		free(minishell->command);
// 		minishell->command = NULL;
// 	}
// }
