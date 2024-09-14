/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 01:13:50 by phwang            #+#    #+#             */
/*   Updated: 2024/09/14 17:15:36 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_unique_dollar(t_data *minishell, char **dollar,
		char **expanded_exported)
{
	*dollar = ft_strdup((*expanded_exported));
	if (!(*dollar))
		return (ft_putstr_fd(EXPAND_MALLOC_ERR, STDERR_FILENO), KO);
	free((*expanded_exported));
	(*expanded_exported) = 0;
	(*expanded_exported) = dollar_expansion(*dollar, D_QUOTE, minishell);
	if (!(*expanded_exported))
		return (free(*dollar), KO);
	free(*dollar);
	*dollar = 0;
	return (OK);
}

int	build_expand_n_replace(char **str_expanded, char ***expanded_exported,
		t_list *tmp_head)
{
	int	y;

	y = -1;
	free((*str_expanded));
	while ((*expanded_exported)[++y])
	{
		(*str_expanded) = strjoin_wfree((*str_expanded),
				(*expanded_exported)[y]);
		if (!(*str_expanded))
			return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
	}
	free_double_char(expanded_exported);
	if ((*str_expanded)[ft_strlen((*str_expanded)) - 1] == ' ')
		(*str_expanded)[ft_strlen((*str_expanded)) - 1] = '\0';
	free(((t_token *)tmp_head->content)->str);
	((t_token *)tmp_head->content)->str = NULL;
	((t_token *)tmp_head->content)->str = ft_strdup((*str_expanded));
	if (!((t_token *)tmp_head->content)->str)
	{
		free((*str_expanded));
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	}
	free((*str_expanded));
	(*str_expanded) = 0;
	return (OK);
}
