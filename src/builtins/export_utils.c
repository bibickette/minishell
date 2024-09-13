/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:07:19 by phwang            #+#    #+#             */
/*   Updated: 2024/09/13 14:14:49 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_in_export(char *var, char **key_export, t_data *minishell)
{
	int	ret;

	if (load_right_export(var, key_export) == KO)
		return (KO);
	ret = export_replacement_tab(&minishell->builtins->export, key_export);
	if (ret == M_KO)
	{
		free(*key_export);
		minishell->last_status = 1;
		return (KO);
	}
	else if (ret == KO)
	{
		if (char_add_back_tab(&minishell->builtins->export, *key_export) == KO)
		{
			free(*key_export);
			minishell->last_status = 1;
			return (KO);
		}
	}
	free(*key_export);
	*key_export = 0;
	minishell->last_status = 0;
	return (OK);
}

int	load_right_export(char *var, char **key_export)
{
	char	*value_export;
	int		i;

	value_export = NULL;
	if (has_equal(var) == OK)
	{
		i = -1;
		while (var[++i])
			if (var[i] == '=')
				break ;
		if (ft_strlen(var) != (size_t)i)
		{
			if (load_value_n_key_export(key_export, &value_export, &var) == KO)
				return (KO);
			(*key_export) = strjoin_wfree((*key_export), value_export);
			free(value_export);
			if (!(*key_export))
				return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
		}
		else
		{
			(*key_export) = ft_strjoin(var, "\"\"");
			if (!(*key_export))
				return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
		}
	}
	if (!(*key_export))
	{
		*key_export = ft_strdup(var);
		if (!(*key_export))
			return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	}
	return (OK);
}

int	export_in_env(char *var, t_data *minishell)
{
	int	ret;

	ret = export_replacement_tab(&minishell->builtins->env, &var);
	if (ret == M_KO)
	{
		minishell->last_status = 1;
		return (KO);
	}
	else if (ret == KO)
	{
		if (char_add_back_tab(&minishell->builtins->env, var) == KO)
		{
			minishell->last_status = 1;
			return (KO);
		}
	}
	minishell->last_status = 0;
	return (OK);
}
