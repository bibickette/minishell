/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:45:57 by phwang            #+#    #+#             */
/*   Updated: 2024/09/14 16:57:33 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	load_export_tab(t_data *minishell, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (char_add_back_tab(&minishell->builtins->export, env[i]) == KO)
			return (ft_putstr_fd(ADD_BACK_TAB_ERR, STDERR_FILENO), KO);
	i = -1;
	while (minishell->builtins->export[++i])
		load_export_w_quote(&minishell->builtins->export[i]);
	return (OK);
}

int	load_export_w_quote(char **export)
{
	char	*value_export;
	char	*key_export;

	if (load_value_n_key_export(&key_export, &value_export, export) == KO)
		return (KO);
	key_export = strjoin_wfree(key_export, value_export);
	free(value_export);
	value_export = 0;
	if (!key_export)
		return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
	free(*export);
	*export = 0;
	*export = ft_strdup(key_export);
	free(key_export);
	key_export = 0;
	if (!*export)
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	return (OK);
}

int	load_value_n_key_export(char **key_export, char **value_export,
		char **export)
{
	int	y;

	y = -1;
	*key_export = ft_strdup(*export);
	if (!*key_export)
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), M_KO);
	while ((*key_export)[++y])
		if ((*key_export)[y] == '=')
			break ;
	(*key_export)[++y] = '\0';
	*value_export = ft_strdup(*export + y);
	if (!*value_export)
	{
		free(*key_export);
		*key_export = 0;
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), M_KO);
	}
	if (put_quote_back(value_export, 34) == KO)
	{
		free(*key_export);
		free(*value_export);
		return (M_KO);
	}
	return (OK);
}
