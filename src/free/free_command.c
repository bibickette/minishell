/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:39:59 by phwang            #+#    #+#             */
/*   Updated: 2024/09/10 18:40:03 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_double_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_command(t_command *command)
{
	if (!command)
		return ;
	if (command->command)
		free(command->command);
	free_double_tab(command->option);
	free_double_tab(command->arg);
	free_double_tab(command->outputs);
	free_double_tab(command->redirections);
	free_double_tab(command->inputs);
	if (command->entire_command)
		free(command->entire_command);
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
	if (command_list)
		free(command_list);
}
