/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:36:12 by phwang            #+#    #+#             */
/*   Updated: 2024/09/29 22:19:58 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

int	open_all_infile(t_data *minishell, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < minishell->nb_hd_files)
	{
		if (open_all_hd_file(minishell, cmd) == KO)
			return (KO);
	}
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

int	open_all_hd_file(t_data *minishell, t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < minishell->nb_hd_files)
	{
		if (minishell->files[i].index_cmd == cmd->index)
		{
			if (open_infile_hd_type(&minishell->files[i]) == KO)
			{
				minishell->last_status = errno;
				return (KO);
			}
		}
	}
	return (OK);
}

int	open_infile_hd_type(t_file *file)
{
	if (file->type == HD_LIMITER_TYPE)
	{
		if (open_infile(file) == KO)
			return (KO);
	}
	return (OK);
}

int	here_doc_create_all(t_data *minishell)
{
	int	i;

	i = -1;
	if (minishell->nb_hd_files == 0)
		return (KO);
	while (++i < minishell->nb_hd_files)
	{
		if (minishell->files[i].type == HD_LIMITER_TYPE)
		{
			heredoc_create(minishell, minishell->files[i].name);
			free(minishell->files[i].name);
			minishell->files[i].name = ft_strdup(HERE_DOC);
			if (!minishell->files[i].name)
				return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), M_KO);
		}
	}
	return (OK);
}
