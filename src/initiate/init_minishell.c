/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:03:33 by phwang            #+#    #+#             */
/*   Updated: 2024/07/13 16:34:48 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_minishell(t_data **minishell)
{
	*minishell = ft_calloc(1, sizeof(t_data));
	if (!minishell)
		return (KO);
	(*minishell)->builtins = ft_calloc(1, sizeof(t_builtin));
	if (!(*minishell)->builtins)
		return (KO);
	return (OK);
}
