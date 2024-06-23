/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 14:52:08 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/23 20:56:31 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing_prompt(char *prompt)
{
	char	**split_prompt;

	check_and_handle_null_prompt(prompt);
	check_and_handle_exit_input(prompt);
	split_prompt = split_prompt(prompt);
}
