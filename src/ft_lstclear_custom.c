/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_custom.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 23:46:08 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/05 18:51:01 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear_custom(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_token	*token;

	tmp = *lst;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		del(token->str);
		tmp = tmp->next;
	}
	ft_lstclear_libft(lst, del);
	free(*lst);
}
