/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_entire_comamnd_bis.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 13:22:57 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/02 18:17:35 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_next(t_list **actual, t_command **actual_command)
{
	*actual = (*actual)->next;
	if (!actual)
		return (0);
	else if (*actual && (*actual)->content)
		*actual_command = (t_command *)(*actual)->content;
	return (1);
}
