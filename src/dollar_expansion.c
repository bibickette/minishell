/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:13:29 by phwang            #+#    #+#             */
/*   Updated: 2024/07/13 00:13:35 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dollar_expansion(char *var, int quote_type, t_data *minishell)
{
	int	i;

	if (!(var[0] == '$'))
		return ;
	if (quote_type == S_QUOTE)
		printf("%s", var);
	else
	{
		var++;
		i = -1;
		while (minishell->builtins->env[++i])
		{
			if (ft_strncmp(minishell->builtins->env[i], var,
					ft_strlen(var)) == 0
				&& minishell->builtins->env[i][ft_strlen(var)] == '=')
			{
				ft_putstr_fd(minishell->builtins->env[i] + ft_strlen(var) + 1,
					STDOUT_FILENO);
				break ;
			}
		}
	}
}
