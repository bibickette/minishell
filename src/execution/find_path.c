/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:08:22 by phwang            #+#    #+#             */
/*   Updated: 2024/09/13 18:43:44 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char *cmd, char **path)
{
	char	*path_cmd;
	int		i;

	i = -1;
	path_cmd = NULL;
	if (!path || !path[0])
		return (NULL);
	while (path[++i])
	{
		if (!cmd)
			return (NULL);
		path_cmd = ft_strjoin(path[i], cmd);
		if (!path_cmd)
			return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), NULL);
		if (access(path_cmd, F_OK | X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
	}
	return (NULL);
}

char	*split_n_path(t_data *minishell, char *cmd_arg, char ***arg,
		t_list *token)
{
	char	*path;

	*arg = ft_split(cmd_arg, ' ');
	if (!arg)
	{
		ft_putstr_fd(SPLIT_ERR, STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (is_builtin((*arg)[0]) == OK)
		path = ft_strdup((*arg)[0]);
	else
		path = find_path(*arg[0], minishell->path);
	if (!path)
	{
		ft_putstr_fd(CMD_NOT_FOUND, STDERR_FILENO);
		ft_putstr_fd((*arg)[0], STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		execve_error_free(minishell, *arg, path, token);
		exit(127);
	}
	return (path);
}
