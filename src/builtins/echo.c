/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:29:34 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/20 17:22:30 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(char **cmd_arg, int fd_out)
{
	int		flag;
	int		i;

	flag = 0 ;
	i = 0;
	if (cmd_arg[1] && is_echo_flag(cmd_arg[1]) == OK)
	{
		flag = 1;
		i = 1;
	}
	while (cmd_arg[++i])
	{
		ft_putstr_fd(cmd_arg[i], fd_out);
		if (cmd_arg[i + 1])
			ft_putstr_fd(" ", fd_out);
	}
	if (flag == 0)
		ft_putstr_fd("\n", fd_out);
}
