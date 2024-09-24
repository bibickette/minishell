/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 00:09:08 by phwang            #+#    #+#             */
/*   Updated: 2024/09/25 00:09:13 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_infile(t_data *minishell, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < minishell->nb_hd_files)
	{
		if (minishell->files[i].index_cmd == cmd->index)
			return (OK);
	}
	i = -1;
	while (++i < cmd->nb_files)
		if (cmd->files[i].type == INFILE_TYPE)
			return (OK);
	return (KO);
}

int	has_outfile(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->nb_files)
		if (cmd->files[i].type == OUTFILE_TYPE
			|| cmd->files[i].type == APPEND_FILE_TYPE)
			return (OK);
	return (KO);
}
