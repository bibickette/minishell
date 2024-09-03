/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 22:46:52 by phwang            #+#    #+#             */
/*   Updated: 2024/06/17 17:16:01 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	cmd_exist(t_pipex *pipex, char **path, char **cmds)
{
	char	**cmd_arg;
	int		y;

	y = -1;
	while (cmds[++y])
	{
		cmd_arg = ft_split(cmds[y], ' ');
		if (!cmd_arg)
			return (return_err_msg(MALLOC_ERROR));
		if (try_path(pipex, path, cmd_arg) == ERROR)
			return (ERROR);
		tab_free(cmd_arg);
	}
	return (OK);
}

int	try_path(t_pipex *pipex, char **path, char **cmd_arg)
{
	static int	cmd = -1;

	cmd++;
	if (cmd_arg[0] == 0)
	{
		pipex->cmds_path[cmd] = ft_strdup("");
		if (!pipex->cmds_path[cmd])
			return (return_err_msg(MALLOC_ERROR));
	}
	else if (has_path(cmd_arg[0]) == OK)
	{
		if (separate_path_cmd(pipex, cmd_arg, cmd) == ERROR)
			return (ERROR);
	}
	else if (test_path(pipex, path, cmd_arg, cmd) == ERROR)
		return (ERROR);
	return (OK);
}

int	test_path(t_pipex *pipex, char **path, char **cmd_arg, int cmd)
{
	char	*path_temp;
	int		i;

	if (pipex->empty_env == 0)
	{
		i = -1;
		while (path[++i])
		{
			path_temp = ft_strjoin(path[i], cmd_arg[0]);
			if (!path_temp)
			{
				tab_free(cmd_arg);
				return (return_err_msg(MALLOC_ERROR));
			}
			if (access(path_temp, F_OK | X_OK) == 0)
				return (cpy_path_cmd(pipex, path_temp, cmd));
			free(path_temp);
		}
	}
	pipex->cmds_path[cmd] = ft_strdup("");
	ft_putstr_fd(CMD_ERROR, STDERR_FILENO);
	ft_putstr_fd(cmd_arg[0], STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	return (OK);
}

void	set_null_struct(t_pipex *pipex)
{
	ft_bzero(pipex, sizeof(t_pipex));
	pipex->fd_in = -1;
	pipex->fd_out = -1;
}
