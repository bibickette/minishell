/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:57 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/07 16:55:29 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote(char **prompt_loop, t_list **token, char buffer[BSIZE])
{
	if (ft_strlen(buffer) > 0)
	{
		if (*token == NULL)
			*token = ft_lstnew_custom(buffer);
		else
			ft_lstadd_back_libft(token, ft_lstnew_custom(buffer));
		ft_bzero(buffer, BSIZE);
	}
	if (have_twin(*prompt_loop) == OK)
	{
		buffer = cpy_twin(prompt_loop, buffer);
		if (*token == NULL)
			*token = ft_lstnew_custom(buffer);
		else
			ft_lstadd_back_libft(token, ft_lstnew_custom(buffer));
		ft_bzero(buffer, BSIZE);
	}
	else
		(*prompt_loop)++;
}
