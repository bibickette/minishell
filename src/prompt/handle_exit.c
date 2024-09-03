/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexplor <hexplor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:08:07 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/03 17:46:45 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exit(t_data *minishell, char *prompt)
{
	if (prompt)
		free(prompt);
	apocalypse(minishell);
	exit(0);
}
