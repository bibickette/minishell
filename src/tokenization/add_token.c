/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:03:30 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/15 15:31:03 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_list **token, char buffer[BSIZE], int type)
{
	t_token	*elem;

	trim_space(buffer);
	if (*token == NULL)
	{
		*token = ft_lstnew_custom(buffer);
		elem = (*token)->content;
		elem->type = type;
	}
	else
	{
		ft_lstadd_back_libft(token, ft_lstnew_custom(buffer));
		elem = (*token)->content;
		elem->type = type;
	}
}
