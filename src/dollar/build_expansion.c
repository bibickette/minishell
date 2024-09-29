/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 01:13:50 by phwang            #+#    #+#             */
/*   Updated: 2024/09/29 21:40:42 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_unique_dollar(t_data *minishell, char **dollar,
		char **expanded_exported)
{
	*dollar = ft_strdup((*expanded_exported));
	if (!(*dollar))
		return (ft_putstr_fd(EXPAND_MALLOC_ERR, STDERR_FILENO), KO);
	free_set_null(expanded_exported);
	(*expanded_exported) = dollar_expansion(*dollar, D_QUOTE, minishell);
	if (!(*expanded_exported))
		return (free(*dollar), KO);
	free_set_null(dollar);
	return (OK);
}

int	build_expand_n_replace(char **str_expanded, char ***expanded_exported,
		char **str)
{
	int	y;

	y = -1;
	free_set_null(str_expanded);
	while ((*expanded_exported)[++y])
	{
		(*str_expanded) = strjoin_wfree((*str_expanded),
				(*expanded_exported)[y]);
		if (!(*str_expanded))
			return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
	}
	free_double_char(expanded_exported);
	if ((*str_expanded)[0] != '\0' && \
		(*str_expanded)[ft_strlen((*str_expanded)) - 1] == ' ')
		(*str_expanded)[ft_strlen((*str_expanded)) - 1] = '\0';
	free(*str);
	*str = NULL;
	*str = ft_strdup((*str_expanded));
	if (!*str)
	{
		free_set_null(str_expanded);
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	}
	free_set_null(str_expanded);
	return (OK);
}

void	free_set_null(char **var)
{
	free(*var);
	*var = NULL;
}

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
