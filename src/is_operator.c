/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_operator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 11:49:57 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/27 11:50:15 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_operator(char *str)
{
	if (!str)
		return (0);
	if (ft_strncmp(str, ">", 2) == 0)
		return (1);
	if (ft_strncmp(str, ">>", 3) == 0)
		return (1);
	if (ft_strncmp(str, "<", 2) == 0)
		return (1);
	if (ft_strncmp(str, "<<", 3) == 0)
		return (1);
	if (ft_strncmp(str, "|", 2) == 0)
		return (1);
	return (0);
}
