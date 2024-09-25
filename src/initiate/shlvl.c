/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:13:57 by phwang            #+#    #+#             */
/*   Updated: 2024/09/25 20:52:29 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_shell_level(t_data *minishell)
{
	char	*full_shlvl;
	int		shell_level;
	char	*shlvl;

	shlvl = NULL;
	load_value(minishell, "SHLVL=", &shlvl, NULL);
	if (!shlvl)
		return (ft_putstr_fd(ERR_SHLVL, STDERR_FILENO), KO);
	shell_level = ft_atoi(shlvl);
	full_shlvl = ft_strdup("SHLVL=");
	free_set_null(&shlvl);
	if (!full_shlvl)
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	shlvl = ft_itoa(++shell_level);
	if (!shlvl)
		return (free_set_null(&full_shlvl), ft_putstr_fd(MALLOC_ERR,
				STDERR_FILENO), KO);
	full_shlvl = strjoin_wfree(full_shlvl, shlvl);
	free_set_null(&shlvl);
	if (!full_shlvl)
		return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
	if (export_in_env(full_shlvl, minishell) == KO)
		return (free_set_null(&full_shlvl), KO);
	return (free_set_null(&full_shlvl), OK);
}

int	load_value(t_data *minishell, char *var, char **to_value, char *cmd_export)
{
	int	i;

	i = -1;
	if (cmd_export)
	{
		if (ft_strncmp(cmd_export, var, ft_strlen(var)) == 0)
		{
			*to_value = ft_strdup(cmd_export + ft_strlen(var));
			if (!*to_value)
				return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
			return (OK);
		}
	}
	while (minishell->builtins->env[++i])
	{
		if (ft_strncmp(minishell->builtins->env[i], var, ft_strlen(var)) == 0)
		{
			*to_value = ft_strdup(minishell->builtins->env[i] + ft_strlen(var));
			if (!*to_value)
				return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
			return (OK);
		}
	}
	return (KO);
}
