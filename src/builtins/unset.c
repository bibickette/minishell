/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:55:56 by phwang            #+#    #+#             */
/*   Updated: 2024/09/04 23:47:36 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(t_builtin *builtins, char *var)
{
	int	i;

	i = -1;
	while (builtins->env[++i])
		if ((ft_strncmp(builtins->env[i], var, ft_strlen(var)) == 0
				&& builtins->env[i][ft_strlen(var)] == '=')
			|| (ft_strncmp(builtins->env[i], var, ft_strlen(var)) == 0
				&& ft_strlen(var) == ft_strlen(builtins->env[i])))
			builtins->env[i][0] = '\0';
}
