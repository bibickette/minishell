/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:34:23 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/27 17:57:25 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*		 S'IL y a un leak cela viens peut etre du fait que le splited_prompt
		 ne reviens pas a son addr de base a la fin de la fonction
*/
static int	**check_error_and_malloc(char **splited_prompt)
{
	if (!splited_prompt)
	{
		ft_putstr_fd("Error: split_commands failed\n", 2);
		return (1);
	}
	return (0);
}

char	**split_commands(char **splited_prompt)
{
	int		i;
	int		j;
	char	**commands;

	if (check_error(splited_prompt) == 1)
		return (NULL);
	i = 1;
	j = 0;
	commands = malloc(sizeof(char *) * (count_commands(splited_prompt) + 1));
	commands[0] = ft_strdup(splited_prompt[0]);
	while (splited_prompt[i])
	{
		if (is_operator(splited_prompt[i]))
		{
			j++;
			commands[j] = handle_op( splited_prompt[i]);
			i++;
			j++;
		}
		else
		{
			commands[j] = command_join(commands[j], splited_prompt[i]);
			i++;
		}
	}
}
