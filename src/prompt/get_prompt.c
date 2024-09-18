/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:40:10 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/18 22:08:18 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	met le prompt dans la variable prompt
*/

char	*get_prompt(t_data **minishell)
{
	char	*prompt;

	prompt = NULL;
	prompt = readline("\x1b[35mTinyShell$ \x1b[0m");
	if (!prompt)
		handle_exit(*minishell, prompt);
	if (ft_strlen(prompt) != 0)
	{
		add_history(prompt);
		add_to_history(minishell, prompt);
	}
	return (prompt);
}
