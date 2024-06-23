/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_and_handle_exit_input.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 15:13:14 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/23 20:49:02 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_and_handle_exit_input(char *prompt)
{
	if (prompt)
	{
		if (ft_strncmp(prompt, "exit\n", ft_strlen(prompt)) == 0)
		{
			free(prompt);
			apocalypse();
			exit(0);
		}
	}
}
