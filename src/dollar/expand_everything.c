/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_everything.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:30:48 by phwang            #+#    #+#             */
/*   Updated: 2024/09/04 22:30:37 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_everything(t_data *minishell, t_list *token)
{
	t_list	*tmp_head;
	char	**dollar_tab;

	tmp_head = token;
	char *str_token_before;
	str_token_before = NULL;
	while (tmp_head)
	{
		if ((((t_token *)tmp_head->content)->quote != S_QUOTE) &&
		str_token_before && ft_strcmp(str_token_before, "<<") != 0)
			if (has_dollar(((t_token *)tmp_head->content)->str) == OK)
				start_expanding(minishell, &dollar_tab, tmp_head);
		if(((t_token *)tmp_head->content)->quote == N_QUOTE)
		{
			char *tmp;
			tmp = ft_strdup(((t_token *)tmp_head->content)->str);
			free(((t_token *)tmp_head->content)->str);
			((t_token *)tmp_head->content)->str = ft_strtrim(tmp, " ");
			free(tmp);
		}
		if (tmp_head->next == NULL)
			break ;
		str_token_before = ((t_token *)tmp_head->content)->str;
		tmp_head = tmp_head->next;
	}
}

int	start_expanding(t_data *minishell, char ***dollar_tab, t_list *tmp_head)
{
	char	*str_expanded;
	char	**expanded_exported;

	str_expanded = ft_strdup(((t_token *)tmp_head->content)->str);
	if (!str_expanded)
		return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
	expanded_exported = ft_split(str_expanded, ' ');
	if (!expanded_exported)
	{
		free(str_expanded);
		return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
	}
	if (set_dollar_n_expand(minishell, dollar_tab, &expanded_exported) == KO)
	{
		free_double_char(expanded_exported);
		free(str_expanded);
		return (KO);
	}
	build_expand_n_replace(&str_expanded, &expanded_exported, tmp_head);
	return (OK);
}

int	set_dollar_n_expand(t_data *minishell, char ***dollar_tab,
		char ***expanded_exported)
{
	char	*dollar;
	int		y;

	y = -1;
	while ((*expanded_exported)[++y])
	{
		if ((*expanded_exported)[y][0] == '$'
			&& has_multiple_dollar((*expanded_exported)[y]) == KO)
		{
			if (build_unique_dollar(minishell, &dollar,
					&(*expanded_exported)[y]) == KO)
				return (KO);
		}
		else if (has_dollar((*expanded_exported)[y]) == OK)
		{
			if (handle_multiple_dollar(minishell, dollar_tab,
					&(*expanded_exported)[y]))
				return (KO);
		}
		(*expanded_exported)[y] = strjoin_wfree((*expanded_exported)[y], " ");
		if (!(*expanded_exported)[y])
			return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
	}
	return (OK);
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
