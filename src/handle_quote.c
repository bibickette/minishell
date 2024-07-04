/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:30:57 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/04 17:19:40 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_quote(char *prompt_loop, t_list *minishell, char buffer[BSIZE])
{
	if (ft_strlen(buffer) > 0)
	{
		if (minishell == NULL)
			minishell = ft_lstnew_custom(buffer);
		else
			ft_lstadd_back_libft(&minishell, ft_lstnew_custom(buffer));
		ft_bzero(buffer, BSIZE);
	}
	if (have_twin(prompt_loop) == OK)
	{
		buffer = cpy_twin(prompt_loop, buffer);
		if (minishell == NULL)
			minishell = ft_lstnew_custom(buffer);
		else
			ft_lstadd_back_libft(&minishell, ft_lstnew_custom(buffer));
	}
	else
		prompt_loop++;
	ft_bzero(buffer, BSIZE);
}
