/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_multiple_dollar.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 00:56:03 by phwang            #+#    #+#             */
/*   Updated: 2024/09/29 18:42:57 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_multiple_dollar(t_data *minishell, char ***dollar_tab,
		char **expanded_exported)
{
	int	z;

	if (first_step_multiple_dollar(minishell, dollar_tab,
			expanded_exported) == KO)
		return (KO);
	free((*expanded_exported));
	z = -1;
	(*expanded_exported) = ft_strdup("");
	if (!(*expanded_exported))
	{
		free_double_char(dollar_tab);
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	}
	while ((*dollar_tab)[++z])
	{
		(*expanded_exported) = strjoin_wfree((*expanded_exported),
				(*dollar_tab)[z]);
		if (!(*expanded_exported))
		{
			free_double_char(dollar_tab);
			return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
		}
	}
	free_double_char(dollar_tab);
	return (OK);
}

int	add_doll_all_tab(t_data *minishell, char ***dollar_tab,
		char *expanded_exported)
{
	int	i;

	if (expanded_exported[0] == '$')
		if (add_doll_first_tab(minishell, dollar_tab) == KO)
			return (KO);
	i = 0;
	while ((*dollar_tab)[++i])
		if (do_the_expansion(minishell, &(*dollar_tab)[i]) == KO)
			return (KO);
	return (OK);
}

int	add_doll_first_tab(t_data *minishell, char ***dollar_tab)
{
	char	*add_first_dol;
	char	*tmp_expanded;

	add_first_dol = ft_strdup("$");
	if (!add_first_dol)
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	add_first_dol = strjoin_wfree(add_first_dol, (*dollar_tab)[0]);
	if (!add_first_dol)
		return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
	tmp_expanded = dollar_expansion(add_first_dol, D_QUOTE, minishell);
	if (!tmp_expanded)
		return (free(add_first_dol), KO);
	free(add_first_dol);
	add_first_dol = 0;
	free((*dollar_tab)[0]);
	(*dollar_tab)[0] = 0;
	(*dollar_tab)[0] = ft_strdup(tmp_expanded);
	if (!(*dollar_tab)[0])
	{
		free(tmp_expanded);
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	}
	free(tmp_expanded);
	return (OK);
}

int	do_the_expansion(t_data *minishell, char **dollar_tab)
{
	char	*tmp_expanded;
	char	*tmp;

	tmp = ft_strdup("$");
	if (!tmp)
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	tmp = strjoin_wfree(tmp, (*dollar_tab));
	if (!tmp)
		return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
	tmp_expanded = dollar_expansion(tmp, D_QUOTE, minishell);
	if (!tmp_expanded)
		return (free(tmp), KO);
	free(tmp);
	tmp = 0;
	free((*dollar_tab));
	*dollar_tab = 0;
	(*dollar_tab) = ft_strdup(tmp_expanded);
	if (!(*dollar_tab))
	{
		free(tmp_expanded);
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	}
	free(tmp_expanded);
	tmp_expanded = 0;
	return (OK);
}

int	first_step_multiple_dollar(t_data *minishell, char ***dollar_tab,
		char **expanded_exported)
{
	(*dollar_tab) = ft_split((*expanded_exported), '$');
	if (!(*dollar_tab))
		return (ft_putstr_fd(SPLIT_ERR, STDERR_FILENO), KO);
	if ((*expanded_exported)[ft_strlen(*expanded_exported) - 1] == '$')
		if (char_add_back_tab(dollar_tab, "") == KO)
			return (KO);
	if (!(*dollar_tab)[0])
	{
		free((*expanded_exported));
		(*expanded_exported) = 0;
		(*expanded_exported) = ft_strdup("");
		if (!(*expanded_exported))
		{
			free_double_char(dollar_tab);
			return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
		}
	}
	else if (add_doll_all_tab(minishell, dollar_tab,
			(*expanded_exported)) == KO)
		return (free_double_char(dollar_tab), KO);
	return (OK);
}
