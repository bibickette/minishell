/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:40:10 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/12 12:40:52 by yantoine         ###   ########.fr       */
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
	prompt = readline("minishell$ ");
	if (!prompt)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		exit(0);
	}
	if (ft_strlen(prompt) != 0)
	{
		add_history(prompt);
		add_to_history(minishell, prompt);
	}
	return (prompt);
}
