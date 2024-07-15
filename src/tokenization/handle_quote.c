/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:57 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/15 15:32:27 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote(char **prompt_loop, t_list **token, char buffer[BSIZE])
{
	int		type;

	type = 0;
	if (ft_strlen(buffer) > 0)
	{
		add_token(token, buffer, type);
		ft_bzero(buffer, BSIZE);
	}
	if (have_twin(*prompt_loop) == OK)
	{
		type = check_type(prompt_loop);
		buffer = cpy_twin(prompt_loop, buffer);
		add_token(token, buffer, type);
		ft_bzero(buffer, BSIZE);
	}
	else
		(*prompt_loop)++;
}
