/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_custom.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 23:46:08 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/04 23:50:52 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear_custom(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_data	*data;

	tmp = *lst;
	while (tmp)
	{
		data = (t_data *)tmp->content;
		del(data->word);
		tmp = tmp->next;
	}
	ft_lstclear_libft(lst, del);
}
