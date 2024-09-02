/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entire_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:37:23 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/02 03:11:52 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_command(t_list *command_list)
{
	printf("check_command\n");
	if (!command_list)
		return (0);
	return (1);
}

static int	init_variable(t_list **actual, \
				t_command **actual_command, t_list *command_list)
{
	printf("init_variable\n");
	*actual = command_list;
	*actual_command = (t_command *)(*actual)->content;
	return (1);
}

static char	*join_c(char *buffer, *string)
{
	char	*join;

	if (!buffer && !string)
		return (NULL);
	else if (buffer && !string)
		return (buffer);
	else if (!buffer && string)
		return (ft_strdup(string));
	else if (buffer && string)
	{
		join = ft_strjoin(buffer, string);
		free(buffer);
		return (join);
	}
	else
		return (NULL);
}

static char	*join_command(t_command *actual_command)
{
	char	*buffer;

	buffer = NULL;
	if (actual_command->command)
		buffer = join_c(buffer, actual_command->command);
	if FINIR OPTION ARG ET TOUT
}

int	set_entire_command(t_list *command_list)
{
	t_list			*actual;
	t_command	*actual_command;

	printf("set_entire_command\n");
	if (check_command(command_list))
	{
		init_variable(actual, actual_command);
		while (actual && actual_command)
		{
			actual_command->entire_command = join_command(actual_command);
			go_next(actual, actual_command);
		}
	}
	return (1);
}
