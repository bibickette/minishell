/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:55:56 by phwang            #+#    #+#             */
/*   Updated: 2024/09/06 21:48:41 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(t_builtin *builtins, char *var)
{
	int	i;

	i = -1;
	while (builtins->env[++i])
		if (the_big_condition(&builtins->env, var, i) == OK)
			builtins->env[i][0] = '\0';
	i = -1;
	while (builtins->export[++i])
		if (the_big_condition(&builtins->export, var, i) == OK)
			builtins->export[i][0] = '\0';
}
