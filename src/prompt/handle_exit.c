/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:08:07 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/20 22:38:02 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exit(t_data *minishell)
{
	int	last_status;

	last_status = minishell->last_status;
	apocalypse(minishell);
	exit(last_status);
}

void	exit_cmd(t_list *token, t_cmd *cmd, t_data *minishell)
{
	if (cmd->cmd_args[1] && is_return_value(cmd->cmd_args[1]) == KO)
	{
		minishell->last_status = 2;
		ft_putstr_fd(EXIT_ERR, STDERR_FILENO);
	}
	else if (cmd->cmd_args[1])
		minishell->last_status = set_exit_arg(ft_atoi(cmd->cmd_args[1]));
	ft_lstclear_custom(&token, free);
	ft_lstclear_custom(&minishell->brut_list, free);
	handle_exit(minishell);
}

int	is_return_value(char *str)
{
	int	i;

	if (!str)
		return (KO);
	i = -1;
	if ((str[0] == '+' || str[0] == '-') && str[1] == '\0')
		return (KO);
	else if (str[0] == '+' || str[0] == '-')
		i++;
	while (str[++i])
		if (ft_isdigit(str[i]) == 0)
			return (KO);
	return (OK);
}

int	set_exit_arg(long int status)
{
	if (status > 255 || status < 0)
		status = status % 256;
	return (status);
}
