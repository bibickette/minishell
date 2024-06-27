/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:36:01 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/27 17:39:18 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_commands(char **splited_prompt)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (splited_prompt[i])
	{
		if (is_operator(splited_prompt[i]))
			count++;
		i++;
	}
	return (count + 1);
}
