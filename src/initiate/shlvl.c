/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 14:13:57 by phwang            #+#    #+#             */
/*   Updated: 2024/09/21 14:14:04 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_shell_level(t_data *minishell)
{
	char	*full_shlvl;
	int		shell_level;
	char	*shlvl;

	shlvl = getenv("SHLVL");
	if (!shlvl)
		return (ft_putstr_fd(ERR_SHLVL, STDERR_FILENO), KO);
	shell_level = ft_atoi(shlvl);
	full_shlvl = ft_strdup("SHLVL=");
	if (!full_shlvl)
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	shlvl = ft_itoa(++shell_level);
	if (!shlvl)
	{
		free_n_set_var_null(&full_shlvl);
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	}
	full_shlvl = strjoin_wfree(full_shlvl, shlvl);
	free_n_set_var_null(&shlvl);
	if (!full_shlvl)
		return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
	if (export_in_env(full_shlvl, minishell) == KO)
		return (free_n_set_var_null(&full_shlvl), KO);
	return (free_n_set_var_null(&full_shlvl), OK);
}
