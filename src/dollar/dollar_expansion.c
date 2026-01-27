/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:13:29 by phwang            #+#    #+#             */
/*   Updated: 2024/09/29 21:47:36 by phwang           ###   ########.fr       */
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
	if (var[1] == '\0')
	{
		expanded = ft_strdup("$");
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
	char	*next_of_var;
	int		i;

	expanded = NULL;
	i = -1;
	next_of_var = keep_next_of_var(&var);
	while (minishell->builtins->env[++i])
	{
		if (ft_strncmp(minishell->builtins->env[i], var, ft_strlen(var)) == 0
			&& minishell->builtins->env[i][ft_strlen(var)] == '=')
		{
			expanded = ft_strdup(minishell->builtins->env[i] + ft_strlen(var)
					+ 1);
			expanded = strjoin_wfree(expanded, next_of_var);
			free_set_null(&next_of_var);
			if (!expanded)
				return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), NULL);
			return (expanded);
		}
	}
	expanded = strjoin_wfree(expanded, next_of_var);
	if (!expanded)
		return (free_set_null(&next_of_var), ft_putstr_fd(STRDUP_ERR, 2), NULL);
	return (free_set_null(&next_of_var), expanded);
}

char	*keep_next_of_var(char **var)
{
	char	*next_var;
	int		i;

	i = -1;
	next_var = NULL;
	while ((*var)[++i])
		if (ft_isalnum((*var)[i]) == 0 && (*var)[i] != '_')
			break ;
	next_var = ft_strdup(*var + i);
	(*var)[i] = '\0';
	return (next_var);
}

/* recoit la variable a etendre vecv le $ et la cherche dans env
malloc et renvoie un char * pour manipuler a la guise lexpansion */
