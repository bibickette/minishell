/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 12:34:23 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/24 14:54:47 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* FINIR cette fonction */
/* BESOIN DE FAIRE FT_REALLOC */
char	***split_commands(char **splited_prompt)
{
	char	***commands;
	
	if (!splited_prompt)
	{
		ft_putstr_fd("Error: split_commands failed\n", 2);
		return (NULL);
	}
	commands = NULL;
	while (*splited_prompt)
	{
		if (ft_strcmp(*splited_prompt, ">") == 0)
	}
}
