/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:58:45 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/13 17:16:35 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_history(t_data *minishell)
{
	t_list	*actual;
	int		i;

	actual = minishell->history;
	i = 0;
	while (actual)
	{
		printf("%d %s", i, (char *)actual->content);
		i++;
		actual = actual->next;
	}
}
