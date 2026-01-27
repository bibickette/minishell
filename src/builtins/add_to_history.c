/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_to_history.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <phwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 15:12:03 by yantoine          #+#    #+#             */
/*   Updated: 2026/01/27 18:16:13 by phwang           ###   ########.fr       */
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
		(*minishell)->history = ft_lstnew(history);
	else
		ft_lstadd_back(&(*minishell)->history, ft_lstnew(history));
}
