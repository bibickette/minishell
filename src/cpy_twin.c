/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpy_twin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:49:01 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/05 17:44:30 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cpy_twin(char *prompt_loop, char buffer[BSIZE])
{
	int			i;
	char	occurence;

	i = 0;
	occurence = *prompt_loop;
	prompt_loop++;
	while (*prompt_loop != occurence)
	{
		buffer[i] = *prompt_loop;
		i++;
		prompt_loop++;
	}
	return (buffer);
}
