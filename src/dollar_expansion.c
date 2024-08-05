/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:13:29 by phwang            #+#    #+#             */
/*   Updated: 2024/08/04 21:51:49 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_expansion(char *var, int quote_type, t_data *minishell)
{
	if (!(var[0] == '$'))
		return (NULL);
	if (quote_type == S_QUOTE)
		return (ft_strdup(var));
	else
	{
		var++;
		if (ft_strcmp(var, "?") == 0)
			return (ft_itoa(minishell->last_status));
		if (*var != '(' && *var != '{')
			return (expansion_no_surround(var, minishell));
		else if (*var == '(')
			return (expansion_parentheses(var, minishell));
	}
	return (NULL);
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
	return (NULL);
}

char	*expansion_parentheses(char *var, t_data *minishell)
{
	char	*trimmed;

	trimmed = NULL;
	if (var[ft_strlen(var) - 1] != ')')
		return (NULL);
	trimmed = ft_strtrim(var, "()");
	if (!trimmed)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), NULL);
	execve_one_cmd(minishell, trimmed, STDOUT_FILENO);
	free(trimmed);
	trimmed = 0;
	trimmed = ft_strdup("");
	if(!trimmed)
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), NULL);
	return (trimmed);
}

/* recoit la variable a etendre vecv le $ et la cherche dans env
malloc et renvoie un char * pour manipuler a la guise lexpansion

prend en compte $(CMD), renvoie "" et execute la cmd, a voir si cest le bon fd

ne gere pas {} */