/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:57 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/11 14:08:34 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote(char **prompt_loop, t_list **token, char buffer[BSIZE])
{
	if (ft_strlen(buffer) > 0)
	{
		add_token(token, buffer);
		ft_bzero(buffer, BSIZE);
	}
	if (have_twin(*prompt_loop) == OK)
	{
		buffer = cpy_twin(prompt_loop, buffer);
		add_token(token, buffer);
		ft_bzero(buffer, BSIZE);
	}
	else
		(*prompt_loop)++;
}
