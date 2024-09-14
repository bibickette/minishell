/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 19:56:23 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/14 15:26:47 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	display_prompt(t_data *minishell)
{
	ft_putstr_fd("minishell$ ", STDOUT_FILENO);
	pwd_cmd(minishell->builtins);
}
