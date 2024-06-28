/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialise_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:00:44 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/27 20:02:25 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**initialise_commands(char **splited_prompt)
{
	char	**commands;

	commands = malloc(sizeof(char *) * (count_commands(splited_prompt) + 1));
	commands[0] = ft_strdup(splited_prompt[0]);
}
