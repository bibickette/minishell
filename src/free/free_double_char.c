/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_double_char.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 21:00:40 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/14 16:20:46 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_char(char ***array)
{
	int	i;

	i = 0;
	if (!array || !*array)
		return ;
	while ((*array)[i])
	{
		if ((*array)[i])
		{
			free((*array)[i]);
			(*array)[i] = NULL;
		}
		i++;
	}
	free(*array);
	*array = NULL;
}
