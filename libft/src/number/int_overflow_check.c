/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_overflow_check.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 23:29:50 by phwang            #+#    #+#             */
/*   Updated: 2024/11/23 00:28:39 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

bool	int_overflow_check(char *str)
{
	int			i;
	static char	max_int[] = "2147483647";
	static char	min_int[] = "-2147483648";

	i = -1;
	if (ft_strlen(str) > 11 || (ft_strlen(str) == 11 && str[0] != '-'))
		return (false);
	if (ft_strlen(str) < 10)
		return (true);
	if (str[0] == '-')
		i++;
	while (str[++i])
	{
		if ((str[i] > min_int[i] && str[0] == '-'))
			return (false);
		else if (str[i] > max_int[i] && str[0] != '-')
			return (false);
	}
	return (true);
}
