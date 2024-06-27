/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_join.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 16:36:35 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/27 17:55:03 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*command_join(char *commands, char *splited_prompt_char)
{
	char	*new_command;

	if (!command || !str2)
	{
		ft_putstr_fd("Error: command_join failed\n", 2);
		return (NULL);
	}
	new_command = ft_strjoin(command, splited_prompt_char);
	if (!new_command)
	{
		ft_putstr_fd("Error: command_join failed\n", 2);
		return (NULL);
	}
	free(commands);
	return (new_command);
}
