/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_history.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:20:47 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/13 16:42:05 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_history(t_data **minishell)
{
	t_list	*actual;
	t_list	*next;

	actual = (*minishell)->history;
	while (actual)
	{
		next = actual->next;
		if (actual->content)
			free(actual->content);
		free(actual);
		actual = next;
	}
}
