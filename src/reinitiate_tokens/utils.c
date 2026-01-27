/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:51:28 by phwang            #+#    #+#             */
/*   Updated: 2024/09/20 17:54:36 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_equal(char *var)
{
	int	i;

	i = -1;
	while (var[++i])
		if (var[i] == '=')
			return (OK);
	return (KO);
}

int	is_echo_flag(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-' || str[1] != 'n')
		return (KO);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (KO);
	}
	return (OK);
}
