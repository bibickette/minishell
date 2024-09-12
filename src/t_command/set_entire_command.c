/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entire_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:37:23 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/11 22:50:05 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_variable(t_list **actual, t_command **actual_command,
		t_list *command_list)
{
	// printf("init_variable\n");
	*actual = command_list;
	*actual_command = (t_command *)(*actual)->content;
	return (1);
}

static char	*join_c(char *buffer, char *string)
{
	char	*join;

	// printf("join_c\n");
	if (!buffer && !string)
		return (NULL);
	else if (buffer && !string)
		return (buffer);
	else if (!buffer && string)
		return (ft_strdup(string));
	else if (buffer && string)
	{
		join = ft_strjoin(buffer, " ");
		free(buffer);
		buffer = join;
		join = ft_strjoin(buffer, string);
		free(buffer);
		return (join);
	}
	else
		return (NULL);
}

static char	*join_double_tab(char *buffer, char **d_tab)
{
	char	*join;
	int		i;

	// printf("join_double_tab\n");
	if (!buffer && !d_tab)
		return (NULL);
	else if (buffer && !d_tab)
		return (buffer);
	else if (!buffer && d_tab)
	{
		i = 0;
		// printf("buffer NULL\n");
		buffer = ft_strdup(d_tab[0]);
		while (d_tab[++i])
		{
			join = ft_strjoin(buffer, " ");
			free(buffer);
			buffer = join;
			join = ft_strjoin(buffer, d_tab[i]);
			free(buffer);
			buffer = join;
			// printf("buffer: %s\n", buffer);
		}
		return (buffer);
	}
	else if (buffer && d_tab)
	{
		i = -1;
		while (d_tab[++i])
		{
			join = ft_strjoin(buffer, " ");
			free(buffer);
			buffer = join;
			join = ft_strjoin(buffer, d_tab[i]);
			free(buffer);
			buffer = join;
			// printf("buffer: %s\n", buffer);
		}
		return (buffer);
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
	if (actual_command->option)
		buffer = join_double_tab(buffer, actual_command->option);
	if (actual_command->arg)
		buffer = join_double_tab(buffer, actual_command->arg);
	return (buffer);
}

int	set_entire_command(t_list *command_list)
{
	t_list		*actual;
	t_command	*actual_command;
	int			ret;

	// printf("set_entire_command\n");
	if (command_list)
	{
		init_variable(&actual, &actual_command, command_list);
		while (actual && actual->content)
		{
			actual_command->entire_command = join_command(actual_command);
			printf("entire_command: %s\n", actual_command->entire_command);
			ret = go_next(&actual, &actual_command);
			printf("ret: %d\n", ret);
			if (ret == 0)
				break ;
		}
	}
	return (1);
}
