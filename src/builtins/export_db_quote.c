/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_db_quote.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 17:33:25 by phwang            #+#    #+#             */
/*   Updated: 2024/08/25 14:18:49 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	export_double_quote(t_data *minishell, char **exported, char *tmp,
// 		char *var)
// {
// 	char	**expanded_exported;
// 	int		y;

// 	expanded_exported = NULL;
// 	*exported = ft_strdup(tmp);
// 	if (!*exported)
// 		return (free_export_malloc(expanded_exported, tmp, *exported));
// 	expanded_exported = ft_split(*exported, ' ');
// 	if (!expanded_exported)
// 		return (free_export_malloc(expanded_exported, tmp, *exported));
// 	if (export_handle_dollar(minishell, &expanded_exported, tmp,
// 			exported) == KO)
// 		return (KO);
// 	free(*exported);
// 	*exported = NULL;
// 	y = -1;
// 	while (expanded_exported[++y])
// 	{
// 		expanded_exported[y] = strjoin_wfree(expanded_exported[y], " ");
// 		if (!expanded_exported[y])
// 			return (free_export_malloc(expanded_exported, tmp, *exported));
// 	}
// 	return (build_the_export(exported, expanded_exported, var, tmp));
// }

int	export_double_quote(t_data *minishell, char **exported, char *tmp,
		char *var)
{
	char	**expanded_exported;
	int		y;

	expanded_exported = NULL;
	*exported = ft_strdup(tmp);
	if (!*exported)
		return (free_export_malloc(expanded_exported, tmp, *exported));
	expanded_exported = ft_split(*exported, ' ');
	if (!expanded_exported)
		return (free_export_malloc(expanded_exported, tmp, *exported));
	if (export_handle_dollar(minishell, &expanded_exported, tmp,
			exported) == KO)
		return (KO);
	free(*exported);
	*exported = NULL;
	y = -1;
	while (expanded_exported[++y])
	{
		expanded_exported[y] = strjoin_wfree(expanded_exported[y], " ");
		if (!expanded_exported[y])
			return (free_export_malloc(expanded_exported, tmp, *exported));
	}
	return (build_the_export(exported, expanded_exported, var, tmp));
}

int	export_handle_dollar(t_data *minishell, char ***expanded_exported,
		char *tmp, char **exported)
{
	char	*dollar;
	int		y;

	y = -1;
	while ((*expanded_exported)[++y])
	{
		if ((*expanded_exported)[y][0] == '$')
		{
			dollar = ft_strdup((*expanded_exported)[y]);
			if (!dollar)
				return (free_export_malloc(*expanded_exported, tmp, *exported));
			free((*expanded_exported)[y]);
			(*expanded_exported)[y] = dollar_expansion(dollar, D_QUOTE,
					minishell);
			free(dollar);
			if (!(*expanded_exported)[y])
				return (free_export_malloc(*expanded_exported, tmp, *exported));
		}
		else if (has_dollar((*expanded_exported)[y]) == OK)
			if (export_dollar_in_str(minishell, &(*expanded_exported)[y], tmp,
				exported) == KO)
				return (KO);
	}
	return (OK);
}
/*
gere les $ expansions seuls
*/

int	export_dollar_in_str(t_data *minishell, char **expanded_exported, char *tmp,
		char **exported)
{
	char	*dollar;
	char	*dup;
	int		i;

	i = -1;
	while ((*expanded_exported)[++i])
		if ((*expanded_exported)[i] == '$')
			break ;
	dup = ft_strdup((*expanded_exported) + i);
	if (!dup)
		return (free_export_malloc(expanded_exported, tmp, *exported));
	dollar = dollar_expansion(dup, D_QUOTE, minishell);
	free(dup);
	if (!dollar)
		return (free_export_malloc(expanded_exported, tmp, *exported));
	if (dollar[0])
	{
		(*expanded_exported)[i] = '\0';
		(*expanded_exported) = strjoin_wfree(*expanded_exported, dollar);
	}
	free(dollar);
	if (!(*expanded_exported))
		return (free_export_malloc(expanded_exported, tmp, *exported));
	return (OK);
}
/*
gere les $ expansions a la fin dune string
*/

int	build_the_export(char **exported, char **expanded_exported, char *var,
		char *tmp)
{
	int	i;
	int	y;

	y = -1;
	i = -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	*exported = ft_calloc(++i + 1, sizeof(char));
	if (!*exported)
		return (free_export_malloc(expanded_exported, tmp, *exported));
	while (++y < i)
		(*exported)[y] = var[y];
	(*exported)[y] = '\0';
	i = -1;
	while (expanded_exported[++i])
	{
		*exported = strjoin_wfree(*exported, expanded_exported[i]);
		if (!*exported)
			return (free_export_malloc(expanded_exported, tmp, *exported));
	}
	free_double_char(expanded_exported);
	if ((*exported)[ft_strlen(*exported) - 1] == ' ')
		(*exported)[ft_strlen(*exported) - 1] = '\0';
	return (OK);
}
/*
build lexport des double quote
*/
