/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 22:17:04 by phwang            #+#    #+#             */
/*   Updated: 2024/09/06 22:17:30 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execve_builtin_or_not(t_data *minish, char **arg, char *path,
		t_list *token)
{
	if (is_builtin(arg[0]) == OK)
	{
		if (execve_builtin(minish, arg) == KO)
		{
			exceve_error_free(minish, arg, path, token);
			exit(EXIT_FAILURE);
		}
		exceve_error_free(minish, arg, path, token);
	}
	else if (execve(path, arg, minish->builtins->env) == KO)
		execve_error(minish, path, arg, token);
}

int	execve_builtin(t_data *minishell, char **arg)
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
	return (OK);
}
