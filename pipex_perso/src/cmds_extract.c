/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds_extract.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 23:36:29 by phwang            #+#    #+#             */
/*   Updated: 2024/06/17 17:07:23 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	has_path(char *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i])
		if (cmd[i] == '/')
			return (OK);
	return (NO);
}

int	separate_path_cmd(t_pipex *pipex, char **cmd_arg, int cmd_nb)
{
	pipex->cmds_path[cmd_nb] = ft_strdup(cmd_arg[0]);
	if (pipex->cmds[cmd_nb])
		free(pipex->cmds[cmd_nb]);
	pipex->cmds[cmd_nb] = extract_cmd(cmd_arg[0]);
	if (!pipex->cmds[cmd_nb])
		return (return_err_msg(MALLOC_ERROR));
	return (OK);
}

char	*extract_cmd(char *cmd_arg)
{
	char	*cmd_crop;
	int		new_len;
	int		len;

	len = ft_strlen(cmd_arg);
	new_len = len;
	while (cmd_arg[--len])
		if (cmd_arg[len] == '/')
			break ;
	len++;
	cmd_crop = ft_calloc((new_len - len + 1), sizeof(char));
	if (!cmd_arg)
		return (NULL);
	new_len = 0;
	while (cmd_arg[len])
	{
		cmd_crop[new_len] = cmd_arg[len];
		new_len++;
		len++;
	}
	cmd_crop[new_len] = 0;
	return (cmd_crop);
}
