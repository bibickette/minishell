/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:12:03 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/13 16:55:08 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_to_history(t_data **minishell, char *command)
{
	char	*history;

	history = ft_strdup(command);
	if (!command)
		return ;
	if (!(*minishell)->history)
		(*minishell)->history = ft_lstnew_libft(history);
	else
		ft_lstadd_front(&(*minishell)->history, ft_lstnew_libft(history));
}
