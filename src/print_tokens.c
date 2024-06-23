/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 23:12:13 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/23 23:27:27 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tokens(char **tokens)
{
	int	i;

	if (!tokens)
	{
		ft_putstr_fd("Error: print_tokens failed\n", 2);
		return ;
	}
	i = 0;
	while (tokens[i])
	{
		printf("Token [%d] = %s\n", i, tokens[i]);
		i++;
	}
}
