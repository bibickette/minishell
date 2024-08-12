/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:29:34 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/12 12:55:33 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	int i;
	int n;

	i = 1;
	n = 0;
	if (args[1] && ft_strcmp(args[1], "-n") == 0)
	{
		n = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr_fd("\n", 1);
	return (0);
}
