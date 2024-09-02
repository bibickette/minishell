/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 20:26:33 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/01 22:57:25 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execution(t_data *minishell)
{
	printf("execution launch\n");
	printf("minishell->command_v1000[0]: %p %s\n", minishell->command_v1000[0], minishell->command_v1000[0]);
	execve_one_cmd(minishell, minishell->command_v1000[0], 1);
}
