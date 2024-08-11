/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 16:22:51 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/11 19:14:10 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_operator(char *str)
{
	if (ft_strncmp(str, ">", 1) == 0)
		return (OK);
	if (ft_strncmp(str, "<", 1) == 0)
		return (OK);
	if (ft_strncmp(str, "|", 1) == 0)
		return (OK);
	return (KO);
}
