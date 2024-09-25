/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 21:55:56 by phwang            #+#    #+#             */
/*   Updated: 2024/09/25 20:17:58 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_cmd(t_data *minishell, char *var)
{
	int	i;

	i = -1;
	if (ft_strcmp(var, "PATH") == 0)
	{
		free_double_char(&minishell->path);
		minishell->path = NULL;
		char_add_back_tab(&minishell->path, "./");
	}
	while (minishell->builtins->env[++i])
		if (the_big_condition(&minishell->builtins->env, var, i) == OK)
			minishell->builtins->env[i][0] = '\0';
	i = -1;
	while (minishell->builtins->export[++i])
		if (the_big_condition(&minishell->builtins->export, var, i) == OK)
			minishell->builtins->export[i][0] = '\0';
}
