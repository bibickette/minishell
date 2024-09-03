/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils02.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <phwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 19:42:13 by phwang            #+#    #+#             */
/*   Updated: 2024/03/20 17:09:57 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../get_next_line.h"

int	first_step(int fd, t_str **head, char **stock)
{
	if (*stock == NULL || **stock == 0)
	{
		if (ft_read(fd, head, stock) == FALSE)
		{
			ft_lstclear(head);
			return (FALSE);
		}
	}
	else
	{
		if (n_stock(head, stock, fd) == FALSE)
		{
			ft_lstclear(head);
			return (FALSE);
		}
	}
	return (TRUE);
}
