/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_no_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:00:38 by phwang            #+#    #+#             */
/*   Updated: 2024/09/25 20:18:16 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_cmd_no_arg(char **export)
{
	int	i;

	if (!export || !export[0])
		return ;
	i = -1;
	while (export[++i])
	{
		if (ft_strcmp(export[i], "") != 0)
		{
			ft_putstr_fd("export ", STDOUT_FILENO);
			ft_putstr_fd(export[i], STDOUT_FILENO);
			ft_putstr_fd("\n", STDOUT_FILENO);
		}
	}
}
