/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 13:23:24 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/23 14:17:46 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_args(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error: too many arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	return (0);
}
