/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:17:04 by phwang            #+#    #+#             */
/*   Updated: 2024/09/18 15:12:57 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execve_builtin(t_data *minishell, char **arg, t_list *token)
{
	int	i;

	i = 0;
	if (first_part_choose_builtin(minishell, arg, token) == KO)
		return (KO);
	if (ft_strcmp(arg[0], "cd") == 0)
	{
		while (arg[i])
			i++;
		if (i > 2)
			return (ft_putstr_fd(TOO_MANY_ARG, STDERR_FILENO), KO);
		cd_cmd(arg[1]);
	}
	else if (ft_strcmp(arg[0], "echo") == 0)
		echo_cmd(token, STDOUT_FILENO);
	else if (ft_strcmp(arg[0], "history") == 0)
		display_history(minishell);
	return (OK);
}

int	first_part_choose_builtin(t_data *minishell, char **arg, t_list *token)
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
		else if (export_all_arg(minishell, token) == KO)
			return (KO);
	}
	else if (ft_strcmp(arg[0], "unset") == 0)
	{
		if (!arg[1])
			return (ft_putstr_fd(NOT_ENOUGH_ARG, STDERR_FILENO), KO);
		else
			while (arg[++i])
				unset_cmd(minishell->builtins, arg[i]);
	}
	return (OK);
}

int	export_all_arg(t_data *minishell, t_list *token)
{
	t_list	*tmp;

	tmp = token;
	while (tmp)
	{
		if ((((t_token *)tmp->content)->type == BUILTIN_TYPE)
			&& ft_strcmp(((t_token *)tmp->content)->str, "export") == 0)
			return (run_list_for_export(minishell, tmp));
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (OK);
}

int	run_list_for_export(t_data *minishell, t_list *tmp)
{
	if (tmp->next == NULL)
		return (OK);
	tmp = tmp->next;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == CMD_TYPE
			|| ((t_token *)tmp->content)->type == BUILTIN_TYPE)
			return (OK);
		else if (((t_token *)tmp->content)->type == ARG_TYPE)
			if (export_cmd_w_arg(((t_token *)tmp->content)->str,
					minishell) == KO)
				return (KO);
		if (tmp->next == NULL)
			return (OK);
		tmp = tmp->next;
	}
	return (OK);
}
