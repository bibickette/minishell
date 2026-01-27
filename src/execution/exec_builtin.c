/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:17:04 by phwang            #+#    #+#             */
/*   Updated: 2024/09/29 16:57:05 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_builtin(t_data *minishell, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (first_part_choose_builtin(minishell, cmd) == KO)
		return (KO);
	if (ft_strcmp(cmd->cmd, "cd") == 0)
	{
		while (cmd->cmd_args[i])
			i++;
		if (i > 2)
			return (ft_putstr_fd(TOO_MANY_ARG, STDERR_FILENO), KO);
		if (cd_cmd(cmd->cmd_args[1]) == KO)
			return (KO);
	}
	else if (ft_strcmp(cmd->cmd, "echo") == 0)
		echo_cmd(cmd->cmd_args, STDOUT_FILENO);
	else if (ft_strcmp(cmd->cmd, "history") == 0)
		display_history(minishell);
	return (OK);
}

int	first_part_choose_builtin(t_data *minishell, t_cmd *cmd)
{
	int	i;

	i = -1;
	if (ft_strcmp(cmd->cmd, "pwd") == 0)
		pwd_cmd(minishell->builtins);
	else if (ft_strcmp(cmd->cmd, "env") == 0)
		env_cmd(minishell->builtins->env);
	else if (ft_strcmp(cmd->cmd, "export") == 0)
	{
		if (!cmd->cmd_args[1])
			export_cmd_no_arg(minishell->builtins->export);
		else if (export_all_arg(minishell, cmd->cmd_args) == KO)
			return (KO);
	}
	else if (ft_strcmp(cmd->cmd, "unset") == 0)
	{
		if (!cmd->cmd_args[1])
			return (ft_putstr_fd(NOT_ENOUGH_ARG, STDERR_FILENO), KO);
		else
			while (cmd->cmd_args[++i])
				unset_cmd(minishell, cmd->cmd_args[i]);
	}
	return (OK);
}

int	export_all_arg(t_data *minishell, char **cmd_arg)
{
	int	i;

	i = 0;
	while (cmd_arg[++i])
	{
		if (cmd_arg[i] && ft_strncmp(cmd_arg[i], "PATH=",
				ft_strlen("PATH=")) == 0)
		{
			unset_cmd(minishell, "PATH");
			if (minishell->path)
				free_double_char(&minishell->path);
			load_path(minishell, 2, cmd_arg[i]);
		}
		if (export_cmd_w_arg(cmd_arg[i], minishell) == M_KO)
			return (KO);
	}
	return (OK);
}
