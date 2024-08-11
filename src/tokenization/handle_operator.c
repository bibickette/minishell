/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:59:10 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/11 17:24:58 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_operator(char **prompt_loop, t_list **token, char buffer[BSIZE])
{
	if (ft_strlen(buffer) > 0)
	{
		add_token(token, buffer);
		ft_bzero(buffer, BSIZE);
	}
	buffer[0] = **prompt_loop;
	(*prompt_loop)++;
	if (**prompt_loop == buffer[0])
	{
		buffer[1] = **prompt_loop;
		(*prompt_loop)++;
	}
	add_token(token, buffer);
	set_type_operator(ft_lstlast(*token)->content);
	ft_bzero(buffer, BSIZE);
}
