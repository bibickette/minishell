/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:00:26 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/12 15:44:19 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_char(char **prompt_loop, t_list **token, char *buffer, int *i)
{
	if (*i == BSIZE)
	{
		if (handle_buffer_overflow(token) != OK)
			return (KO);
		*i = 0;
	}
	else if (**prompt_loop == 34 || **prompt_loop == 39)
	{
		if (handle_quote(prompt_loop, token, buffer) == KO)
			return (KO);
		*i = 0;
	}
	else if (check_operator(*prompt_loop) == OK)
	{
		handle_operator(prompt_loop, token, buffer);
		*i = 0;
	}
	else if (**prompt_loop == ' ')
	{
		handle_space(prompt_loop, token, buffer);
		*i = 0;
	}
	else
		make_theim_increment(prompt_loop, buffer, i);
	return (OK);
}

void	make_theim_increment(char **prompt_loop, char *buffer, int *i)
{
	buffer[*i] = **prompt_loop;
	(*i)++;
	(*prompt_loop)++;
}
