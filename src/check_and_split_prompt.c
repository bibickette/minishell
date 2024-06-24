/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_split_prompt.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:26:54 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/24 12:28:09 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**check_and_split_prompt(char *prompt)
{
	char	**splited_prompt;

	if (!prompt)
	{
		ft_putstr_fd("Error: check_and_split_prompt failed\n", 2);
		return (NULL);
	}
	splited_prompt = NULL;
	check_and_handle_null_prompt(prompt);
	check_and_handle_exit_input(prompt);
	splited_prompt = split_prompt(prompt);
	if (!splited_prompt)
	{
		ft_putstr_fd("Error: check_and_split_prompt failed\n", 2);
		return (NULL);
	}
	return (splited_prompt);
}
