/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pile_clear.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 14:12:58 by phwang            #+#    #+#             */
/*   Updated: 2024/03/16 20:40:32 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	pile_clear(t_list **head)
{
	if (*head != NULL)
	{
		pile_clear(&((*head)->next));
		if ((*head)->content != NULL)
		{
			free((*head)->content);
			(*head)->content = NULL;
		}
		free(*head);
		*head = NULL;
	}
}
