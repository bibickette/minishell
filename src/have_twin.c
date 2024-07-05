/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   have_twin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 10:59:17 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/05 17:38:53 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	have_twin(char *prompt)
{
	int		i;
	char	twin;

	i = 1;
	twin = prompt[0];
	while (prompt[i])
	{
		if (prompt[i] == twin)
			if (prompt[i - 1] != twin)
				return (OK);
		i++;
	}
	return (KO);
}
