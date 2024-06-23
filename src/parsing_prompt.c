/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:52:08 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/23 23:38:30 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	s'occuper de la commande pour le mettre avant la tokenisation	*/
char	**parsing_prompt(char *prompt)
{
	char	**splited_prompt;
	char	***commands;
	char	**tokened_prompt;

	if (!prompt)
	{
		ft_putstr_fd("Error: parsing_prompt failed\n", 2);
		return (NULL);
	}
	commands = NULL;
	splited_prompt = NULL;
	tokens = NULL;
	check_and_handle_null_prompt(prompt);
	check_and_handle_exit_input(prompt);
	splited_prompt = split_prompt(prompt);
	tokened_prompt = tokenize_prompt(splited_prompt);
	return (tokens);
}
