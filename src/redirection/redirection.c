/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 22:05:44 by phwang            #+#    #+#             */
/*   Updated: 2024/09/20 20:54:28 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_in(t_data *minishell, t_file *files, t_cmd *cmd, int std_in)
{
	int	i;

	i = -1;
	if (minishell->nb_hd_files > 0)
	{
		while (files[++i].name)
			if (files[i].fd != KO)
				if (dup2(files[i].fd, std_in) < 0)
					return (perror(DUP_ERR), errno);
	}
	if (cmd->nb_files == 0)
		return (OK);
	i = -1;
	while (cmd->files[++i].name)
		if (cmd->files[i].type == INFILE_TYPE)
			if (cmd->files[i].fd != KO)
				if (dup2(cmd->files[i].fd, std_in) < 0)
					return (perror(DUP_ERR), errno);
	return (OK);
}

int	redirection_out(t_cmd *cmd, t_file *files, int std_out)
{
	int	i;

	if (!files || cmd->nb_files == 0)
		return (OK);
	i = -1;
	while (files[++i].name)
	{
		if (files[i].type == OUTFILE_TYPE || files[i].type == APPEND_FILE_TYPE)
		{
			if (files[i].fd != KO)
			{
				if (dup2(files[i].fd, std_out) < 0)
					return (perror(DUP_ERR), errno);
			}
			else
				return (KO);
		}
	}
	return (OK);
}
