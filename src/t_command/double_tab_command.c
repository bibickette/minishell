/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_tab_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 14:05:29 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/06 14:17:38 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**double_tab_command(t_list *command_list)
{
	int					i;
	char				**tab_command;
	t_list			*actual;
	t_command	*content;

	i = 0;
	actual = command_list;
	if (!actual)
		return (NULL);
	content = (t_command *)actual->content;
	tab_command = ft_calloc(ft_lstsize(command_list) + 1, sizeof(char *));
	if (!tab_command)
		return (NULL);
	while (actual)
	{
		tab_command[i] = content->command;
		tab_command[i + 1] = NULL;
		actual = actual->next;
		if (actual && actual->content)
			content = (t_command *)actual->content;
		i++;
	}
	return (tab_command);
}
