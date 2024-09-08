/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:13:29 by phwang            #+#    #+#             */
/*   Updated: 2024/09/06 19:58:52 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_expansion(char *var, int quote_type, t_data *minishell)
{
	char	*expanded;

	expanded = NULL;
	if (!var || !(var[0] == '$'))
	{
		expanded = ft_strdup("");
		if (!expanded)
			return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), NULL);
		return (expanded);
	}
	return (create_expansion_dollar(minishell, var, expanded, quote_type));
}

char	*create_expansion_dollar(t_data *minishell, char *var, char *expanded,
		int quote_type)
{
	if (quote_type == S_QUOTE)
	{
		expanded = ft_strdup(var);
		if (!expanded)
			return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), NULL);
	}
	else
	{
		var++;
		if (ft_strcmp(var, "?") == 0)
		{
			expanded = ft_itoa(minishell->last_status);
			if (!expanded)
				return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), NULL);
		}
		else
			return (expansion_no_surround(var, minishell));
	}
	return (expanded);
}

char	*expansion_no_surround(char *var, t_data *minishell)
{
	char	*expanded;
	int		i;

	expanded = NULL;
	i = -1;
	while (minishell->builtins->env[++i])
	{
		if (ft_strncmp(minishell->builtins->env[i], var, ft_strlen(var)) == 0
			&& minishell->builtins->env[i][ft_strlen(var)] == '=')
		{
			expanded = ft_strdup(minishell->builtins->env[i] + ft_strlen(var)
					+ 1);
			if (!expanded)
				return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), NULL);
			return (expanded);
		}
	}
	expanded = ft_strdup("");
	if (!expanded)
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), NULL);
	return (expanded);
}

/* recoit la variable a etendre vecv le $ et la cherche dans env
malloc et renvoie un char * pour manipuler a la guise lexpansion */

int	has_multiple_dollar(char *var)
{
	int	i;
	int	dollar;

	i = -1;
	dollar = 0;
	while (var[++i])
		if (var[i] == '$')
			dollar++;
	if (dollar > 1)
		return (OK);
	return (KO);
}

int	has_dollar(char *var)
{
	int	i;

	i = -1;
	while (var[++i])
		if (var[i] == '$')
			return (OK);
	return (KO);
}
