/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:18:41 by phwang            #+#    #+#             */
/*   Updated: 2024/07/12 22:03:48 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_cmd(char **env)
{
	int	i;

	if (!env || !env[0])
		return ;
	i = -1;
	while (env[++i])
	{
		ft_putstr_fd(env[i], STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
}
