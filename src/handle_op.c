/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_op.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:22:36 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/30 16:45:55 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_op(char *splited_prompt_char)
{
	char	*command;

	if (!splited_prompt_char)
	{
		ft_putstr_fd("Error: handle_op failed\n", 2);
		return (NULL);
	}
	command = ft_strdup(splited_prompt_char);
	if (!command)
	{
		ft_putstr_fd("Error: handle_op failed\n", 2);
		return (NULL);
	}
	return (command);
}
