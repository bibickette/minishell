/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:17:04 by phwang            #+#    #+#             */
/*   Updated: 2024/09/10 20:16:35 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_builtin(t_data *minishell, char **arg, t_list *token)
{
	int	i;

	i = -1;
	if (ft_strcmp(arg[0], "pwd") == 0)
		pwd_cmd(minishell->builtins);
	else if (ft_strcmp(arg[0], "env") == 0)
		env_cmd(minishell->builtins->env);
	else if (ft_strcmp(arg[0], "export") == 0)
	{
		if (!arg[1])
			export_cmd_no_arg(minishell->builtins->export);
		else
			while (arg[++i])
				export_cmd_w_arg(arg[i], minishell);
	}
	else if (ft_strcmp(arg[0], "unset") == 0)
	{
		if (!arg[1])
			return (ft_putstr_fd(NOT_ENOUGH_ARG, STDERR_FILENO), KO);
		else
			while (arg[++i])
				unset_cmd(minishell->builtins, arg[i]);
	}
	else if (ft_strcmp(arg[0], "cd") == 0)
	{
		cd_cmd(arg[1]);
	}
	else if (ft_strcmp(arg[0], "echo") == 0)
		echo_cmd(token, STDOUT_FILENO);
	else if (ft_strcmp(arg[0], "exit") == 0)
		return (M_KO);
	else if (ft_strcmp(arg[0], "history") == 0)
		display_history(minishell);
	return (OK);
}
