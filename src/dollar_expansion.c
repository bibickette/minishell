/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:13:29 by phwang            #+#    #+#             */
/*   Updated: 2024/07/14 23:24:24 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_expansion(char *var, int quote_type, t_data *minishell)
{
	char	*expanded;
	int		i;

	if (!(var[0] == '$'))
		return (NULL);
	expanded = NULL;
	if (quote_type == S_QUOTE)
		printf("%s", var);
	else
	{
		var++;
		i = -1;
		if (*var == '?' && *var + 1 == '\0')
			return (ft_itoa(minishell->last_status));
		while (minishell->builtins->env[++i])
			if (ft_strncmp(minishell->builtins->env[i], var,
					ft_strlen(var)) == 0
				&& minishell->builtins->env[i][ft_strlen(var)] == '=')
				return (ft_strdup(minishell->builtins->env[i] + ft_strlen(var)
						+ 1));
	}
	return (expanded);
}

/* recoit la variable a etendre et la cherche dans env
malloc et renvoie un char * pour manipuler a la guise lexpansion */