/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:00:26 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/11 19:14:24 by phwang           ###   ########.fr       */
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
	{
		buffer[*i] = **prompt_loop;
		(*i)++;
		(*prompt_loop)++;
	}
	return (OK);
}
