/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_handle_null_prompt.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:07:57 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/23 21:58:49 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_and_handle_null_prompt(char *prompt)
{
	if (!prompt)
	{
		apocalypse();
		exit(EXIT_FAILURE);
	}
}
