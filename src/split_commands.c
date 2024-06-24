/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:34:23 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/24 16:46:03 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*		 S'IL y a un leak cela viens peut etre du fait que le splited_prompt
		 ne reviens pas a son addr de base a la fin de la fonction
*/
char	***split_commands(char **splited_prompt)
{
	char	***commands;
	
	if (!splited_prompt)
	{
		ft_putstr_fd("Error: split_commands failed\n", 2);
		return (NULL);
	}
	commands = malloc(sizeof(char **) * 2);
	if (!commands)
	{
		ft_putstr_fd("Error: split_commands failed\n", 2);
		return (NULL);
	}
	while (*splited_prompt)
	{
		splited_prompt += 1;
	}
}
