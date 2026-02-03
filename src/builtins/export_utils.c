/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <phwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:07:19 by phwang            #+#    #+#             */
/*   Updated: 2026/02/03 18:31:50 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_in_export(char *var, char **key_export, t_data *minishell)
{
	int	ret;

	if (load_right_export(var, key_export) == M_KO)
		return (M_KO);
	if (!minishell->builtins->export)
		ret = KO;
	else
		ret = export_replacement_tab(&minishell->builtins->export, key_export);
	if (ret == M_KO)
	{
		free_set_null(key_export);
		minishell->last_status = 1;
		return (M_KO);
	}
	else if (ret == KO)
	{
		if (char_add_back_tab(&minishell->builtins->export, *key_export) == false)
		{
			free_set_null(key_export);
			minishell->last_status = 1;
			return (M_KO);
		}
	}
	free_set_null(key_export);
	return (OK);
}

int	load_right_export(char *var, char **key_export)
{
	if (has_equal(var) == OK)
		if (load_export_w_equal(var, key_export) == M_KO)
			return (M_KO);
	if (!(*key_export))
	{
		*key_export = ft_strdup(var);
		if (!(*key_export))
			return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), M_KO);
	}
	return (OK);
}

int	load_export_w_equal(char *var, char **key_export)
{
	char	*value_export;
	int		i;

	value_export = NULL;
	i = -1;
	while (var[++i])
		if (var[i] == '=')
			break ;
	if (ft_strlen(var) != (size_t)i)
	{
		if (load_value_n_key_export(key_export, &value_export, &var) == KO)
			return (M_KO);
		(*key_export) = strjoin_wfree((*key_export), value_export);
		free_set_null(&value_export);
		if (!(*key_export))
			return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), M_KO);
	}
	else
	{
		(*key_export) = ft_strjoin(var, "\"\"");
		if (!(*key_export))
			return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), M_KO);
	}
	return (OK);
}

int	export_in_env(char *var, t_data *minishell)
{
	int	ret;

	if (!minishell->builtins->env)
		ret = KO;
	else
		ret = export_replacement_tab(&minishell->builtins->env, &var);
	if (ret == M_KO)
	{
		minishell->last_status = 1;
		return (M_KO);
	}
	else if (ret == KO)
	{
		if (char_add_back_tab(&minishell->builtins->env, var) == false)
		{
			minishell->last_status = 1;
			return (M_KO);
		}
	}
	return (OK);
}
