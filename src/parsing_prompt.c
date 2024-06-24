/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:52:08 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/24 14:54:16 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	s'occuper de la commande pour le mettre avant la tokenisation	*/
char	***parsing_prompt(char *prompt)
{
	char	**splited_prompt;
	char	***commands;

	if (!prompt)
	{
		ft_putstr_fd("Error: parsing_prompt failed\n", 2);
		return (NULL);
	}
	commands = NULL;
	splited_prompt = NULL;
	splited_prompt = check_and_split_prompt(prompt);
	commands = split_commands(splited_prompt);
	commands = tokenize_commands(commands);
	return (tokens);
}
