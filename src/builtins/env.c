/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:18:41 by phwang            #+#    #+#             */
/*   Updated: 2024/08/12 01:22:59 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(char **env, t_list *export)
{
	int	i;

	if (!env || !env[0])
		return ;
	i = -1;
	while (env[++i])
	{
		if (ft_strcmp(env[i], "") != 0)
		{
			ft_putstr_fd(env[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
	env_cmd_check_export(export);
}

void	env_cmd_check_export(t_list *export)
{
	char	*tmp;

	if (export)
	{
		while (export)
		{
			tmp = (char *)export->content;
			if (tmp)
			{
				ft_putstr_fd(tmp, STDOUT_FILENO);
				ft_putstr_fd("\n", STDOUT_FILENO);
			}
			if (export->next == NULL)
				break ;
			export = export->next;
		}
	}
}
