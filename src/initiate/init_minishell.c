/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 21:03:33 by phwang            #+#    #+#             */
/*   Updated: 2024/09/19 01:43:15 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_signal = 0;

int	init_minishell(t_data **minishell)
{
	*minishell = ft_calloc(1, sizeof(t_data));
	if (!minishell)
		return (KO);
	(*minishell)->builtins = ft_calloc(1, sizeof(t_builtin));
	if (!(*minishell)->builtins)
		return (KO);
	(*minishell)->here_doc = KO;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	return (OK);
}
