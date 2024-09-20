/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:36:12 by phwang            #+#    #+#             */
/*   Updated: 2024/09/20 19:06:50 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

int	open_all_infile(t_data *minishell, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->nb_files)
	{
		if (open_infile_type(&cmd->files[i]) == KO)
		{
			minishell->last_status = errno;
			return (KO);
		}
	}
	return (OK);
}

int	open_all_outfile(t_data *minishell, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->nb_files)
	{
		if (open_outfile_type(&cmd->files[i]) == KO)
		{
			minishell->last_status = errno;
			return (KO);
		}
	}
	return (OK);
}

int	open_all_hd_file(t_data *minishell)
{
	int	i;

	i = -1;
	while (++i < minishell->nb_hd_files)
	{
		if (open_infile_hd_type(minishell, &minishell->files[i]) == KO)
		{
			minishell->last_status = errno;
			return (KO);
		}
	}
	return (OK);
}

int	open_infile_hd_type(t_data *minishell, t_file *file)
{
	if (file->type == HD_LIMITER_TYPE)
	{
		heredoc_create(minishell, file->name);
		free(file->name);
		file->name = ft_strdup(HERE_DOC);
		if (open_infile(file) == KO)
			return (KO);
	}
	return (OK);
}
