/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:36:24 by phwang            #+#    #+#             */
/*   Updated: 2024/09/29 22:38:40 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_cmd(t_list *token, t_cmd *cmd, t_data *minishell)
{
	int	cmd_size;

	cmd_size = 0;
	while (cmd->cmd_args[cmd_size])
		cmd_size++;
	if (cmd_size > 2 && cmd->cmd_args[1]
		&& is_return_value(cmd->cmd_args[1]) == OK)
	{
		minishell->last_status = 1;
		return (ft_putstr_fd(TOO_MANY_ARG, STDERR_FILENO));
	}
	if (cmd->cmd_args[1] && is_return_value(cmd->cmd_args[1]) == KO)
	{
		minishell->last_status = 2;
		ft_putstr_fd(EXIT_ERR, STDERR_FILENO);
	}
	else if (cmd->cmd_args[1])
		minishell->last_status = set_exit_arg(ft_atol(cmd->cmd_args[1]));
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
	if (((str[0] == '-' || str[0] == '+') && i > 20) || ((str[0] != '-'
				&& str[0] != '+') && i > 19))
		return (KO);
	if ((str[0] == '-' && is_smaller_than_longmin(str) == KO) || ((str[0] != '-'
				|| str[0] == '+')
			&& 9223372036854775807 < (unsigned long)ft_atol(str)))
		return (KO);
	return (OK);
}

long long int	set_exit_arg(long long int status)
{
	if (status > 255 || status < 0)
		status = status % 256;
	return (status);
}

int	is_smaller_than_longmin(char *str)
{
	static char	min[] = "-9223372036854775808";
	int			i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] > min[i])
			return (KO);
		i++;
	}
	return (OK);
}
