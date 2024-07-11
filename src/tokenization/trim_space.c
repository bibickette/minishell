/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:53:23 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/11 17:32:06 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int ft_is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void	trim_space(char buffer[BSIZE])
{
	int		i;
	int		j;
	char	tmp[BSIZE];

	i = 0;
	j = 0;
	bzero(tmp, BSIZE);
	while (buffer[i] && ft_is_space(buffer[i]))
		i++;
	while (buffer[i])
	{
		tmp[j] = buffer[i];
		i++;
		j++;
	}
	j--;
	while (j >= 0 && ft_is_space(tmp[j]))
	{
		tmp[j] = '\0';
		j--;
	}
	bzero(buffer, BSIZE);
	ft_strlcpy(buffer, tmp, BSIZE);
}
