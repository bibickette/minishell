/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_tab_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:05:29 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/10 20:58:45 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	size_list(t_list *command_list)
{
	int		size;
	t_list	*actual;

	size = 0;
	actual = command_list;
	while (actual)
	{
		size++;
		actual = actual->next;
	}
	return (size);
}

char	**double_tab_command(t_list *command_list)
{
	int			i;
	int			size;
	char		**tab_command;
	t_list		*actual;
	t_command	*content;

	i = 0;
	actual = command_list;
	if (!actual)
		return (NULL);
	content = (t_command *)actual->content;
	size = size_list(command_list);
	tab_command = ft_calloc(size + 1, sizeof(char *));
	while (actual)
	{
		tab_command[i] = content->entire_command;
		actual = actual->next;
		if (actual && actual->content)
			content = (t_command *)actual->content;
		i++;
	}
	tab_command[i] = NULL;
	return (tab_command);
}
