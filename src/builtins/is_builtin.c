/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:57:10 by phwang            #+#    #+#             */
/*   Updated: 2024/08/11 20:57:21 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *command)
{
	if (!command)
		return (KO);
	if (ft_strcmp(command, "echo") == 0)
		return (OK);
	if (ft_strcmp(command, "cd") == 0)
		return (OK);
	if (ft_strcmp(command, "pwd") == 0)
		return (OK);
	if (ft_strcmp(command, "export") == 0)
		return (OK);
	if (ft_strcmp(command, "unset") == 0)
		return (OK);
	if (ft_strcmp(command, "env") == 0)
		return (OK);
	if (ft_strcmp(command, "exit") == 0)
		return (OK);
	if (ft_strcmp(command, "history") == 0)
		return (OK);
	return (KO);
}
