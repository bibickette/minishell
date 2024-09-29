/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_everything.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 19:30:48 by phwang            #+#    #+#             */
/*   Updated: 2024/09/29 21:48:23 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_everything(t_data *minishell, t_list *token)
{
	t_list	*tmp_head;
	char	**dollar_tab;
	char	*str_token_before;

	tmp_head = token;
	str_token_before = NULL;
	while (tmp_head)
	{
		if (right_condition_for_expand(tmp_head, str_token_before) == OK)
			if (has_dollar(((t_token *)tmp_head->content)->str) == OK)
				if (start_expanding(minishell, &dollar_tab,
						&((t_token *)tmp_head->content)->str) == KO)
					return (KO);
		if (((t_token *)tmp_head->content)->quote == N_QUOTE)
			if (trim_token(tmp_head) == M_KO)
				return (KO);
		if (tmp_head->next == NULL)
			break ;
		str_token_before = ((t_token *)tmp_head->content)->str;
		tmp_head = tmp_head->next;
	}
	return (OK);
}

int	trim_token(t_list *tmp_head)
{
	char	*tmp;

	if (((t_token *)tmp_head->content)->str[0])
	{
		tmp = ft_strdup(((t_token *)tmp_head->content)->str);
		if (!tmp)
			return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), M_KO);
		free(((t_token *)tmp_head->content)->str);
		((t_token *)tmp_head->content)->str = NULL;
		((t_token *)tmp_head->content)->str = ft_strtrim(tmp, " ");
		free_set_null(&tmp);
		if (!((t_token *)tmp_head->content)->str)
			return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), M_KO);
		return (OK);
	}
	return (OK);
}

int	right_condition_for_expand(t_list *tmp_head, char *str_token_before)
{
	if ((((t_token *)tmp_head->content)->quote != S_QUOTE) && (!str_token_before
			|| (str_token_before && ft_strcmp(str_token_before, "<<") != 0)))
		return (OK);
	return (KO);
}

int	start_expanding(t_data *minishell, char ***dollar_tab, char **str)
{
	char	*str_expanded;
	char	**expanded_exported;

	str_expanded = ft_strdup(*str);
	if (!str_expanded)
		return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
	expanded_exported = split_w_space(str_expanded);
	if (!expanded_exported)
	{
		free_set_null(&str_expanded);
		return (ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO), KO);
	}
	if (set_dollar_n_expand(minishell, dollar_tab, &expanded_exported) == KO)
	{
		free_double_char(&expanded_exported);
		return (free_set_null(&str_expanded), KO);
	}
	if (build_expand_n_replace(&str_expanded, &expanded_exported, str) == KO)
		return (KO);
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
					&(*expanded_exported)[y]) == KO)
				return (KO);
		}
	}
	return (OK);
}
