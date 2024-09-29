/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:40:10 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/29 14:53:46 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	met le prompt dans la variable prompt
*/

void	get_prompt(t_data **minishell)
{
	(*minishell)->prompt = NULL;
	(*minishell)->prompt = readline("\x1b[35m\1TinyShell$ \2\x1b[0m");
	if (!(*minishell)->prompt)
	{
		handle_signals(*minishell);
		handle_exit(*minishell);
	}
	if (ft_strlen((*minishell)->prompt) != 0)
	{
		add_history((*minishell)->prompt);
		add_to_history(minishell, (*minishell)->prompt);
	}
}
