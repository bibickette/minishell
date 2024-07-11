/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_operator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:59:10 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/11 14:09:29 by yantoine         ###   ########.fr       */
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
	ft_bzero(buffer, BSIZE);
}
