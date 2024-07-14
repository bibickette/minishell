/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 21:08:22 by phwang            #+#    #+#             */
/*   Updated: 2024/07/14 23:14:59 by phwang           ###   ########.fr       */
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
		return (path_cmd);
	while (path[++i])
	{
		path_cmd = ft_strjoin(path[i], cmd);
		if (!path_cmd)
		{
			ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO);
			return (NULL);
		}
		if (access(path_cmd, F_OK | X_OK) == 0)
			return (path_cmd);
		free(path_cmd);
	}
	path_cmd = ft_strdup("");
	return (path_cmd);
}
