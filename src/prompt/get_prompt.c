/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:40:10 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/20 22:27:23 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	met le prompt dans la variable prompt
*/

void	get_prompt(t_data **minishell)
{
	(*minishell)->prompt = NULL;
	(*minishell)->prompt = readline("\x1b[35mTinyShell$ \x1b[0m");
	if (!(*minishell)->prompt)
	{
		(*minishell)->last_status = 1;
		handle_exit(*minishell);
	}
	if (ft_strlen((*minishell)->prompt) != 0)
	{
		add_history((*minishell)->prompt);
		add_to_history(minishell, (*minishell)->prompt);
	}
}
