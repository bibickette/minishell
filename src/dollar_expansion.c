/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:13:29 by phwang            #+#    #+#             */
/*   Updated: 2024/08/28 18:42:37 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_expansion(char *var, int quote_type, t_data *minishell)
{
	char	*expanded;

	if (!var || !(var[0] == '$'))
		return (NULL);
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
	return (expansion_no_surround_list(var, minishell));
}

char	*expansion_no_surround_list(char *var, t_data *minishell)
{
	t_list	*tmp;
	char	*expanded;

	tmp = minishell->builtins->export;
	while (tmp)
	{
		if (ft_strncmp((char *)tmp->content, var, ft_strlen(var)) == 0
			&& ((char *)tmp->content)[ft_strlen(var)] == '=')
		{
			expanded = ft_strdup((char *)tmp->content + ft_strlen(var) + 1);
			if (!expanded)
				return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), NULL);
			return (expanded);
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	expanded = ft_strdup("");
	if (!expanded)
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), NULL);
	return (expanded);
}

/* recoit la variable a etendre vecv le $ et la cherche dans env
malloc et renvoie un char * pour manipuler a la guise lexpansion */