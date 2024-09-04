/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexplor <hexplor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:29:41 by phwang            #+#    #+#             */
/*   Updated: 2024/09/04 19:05:31 by hexplor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	ft_lstadd_back_libft(t_list **lst, t_list *new)
{
	if (!(*lst))
		*lst = new;
	else
		ft_lstlast(*lst)->next = new;
}
