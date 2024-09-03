/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:21:33 by phwang            #+#    #+#             */
/*   Updated: 2024/09/03 18:12:00 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_file(t_data *minishell, t_file *file)
{
	if (file->type == INFILE_TYPE)
		open_infile(file);
	else if (file->type == OUTFILE_TYPE)
		open_outfile(file);
	else if (file->type == APPEND_FILE_TYPE)
		open_append_outfile(file);
	else if (file->type == HD_LIMITER_TYPE)
	{
		heredoc_create(minishell, file->name);
		file->fd = KO;
	}
	return (OK);
}

void	open_infile(t_file *file)
{
	if ((access(file->name, F_OK) == 0) && (access(file->name, R_OK) == 0))
	{
		file->fd = open(file->name, O_RDONLY);
		if (file->fd == -1)
			return (ft_putstr_fd(INFILE_ERROR_FD, STDERR_FILENO));
		file->is_open = OK;
	}
	else if ((access(file->name, F_OK) == 0) && (access(file->name, R_OK) != 0))
	{
		perror(FILE_ERR);
		ft_putstr_fd("File error : ", STDERR_FILENO);
		ft_putstr_fd(file->name, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		file->fd = KO;
	}
	else
	{
		file->fd = KO;
		ft_putstr_fd(FILE_NOT_EXIST, STDERR_FILENO);
	}
}

void	open_outfile(t_file *file)
{
	if ((access(file->name, F_OK) == 0) && (access(file->name, W_OK) != 0))
	{
		perror(FILE_ERR);
		ft_putstr_fd("File error : ", STDERR_FILENO);
		ft_putstr_fd(file->name, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		file->fd = KO;
	}
	else
	{
		file->fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file->fd == -1)
			return (ft_putstr_fd(OUTFILE_ERROR_FD, STDERR_FILENO));
		file->is_open = OK;
	}
}

void	open_append_outfile(t_file *file)
{
	if ((access(file->name, F_OK) == 0) && (access(file->name, W_OK) != 0))
	{
		perror(FILE_ERR);
		ft_putstr_fd("File error : ", STDERR_FILENO);
		ft_putstr_fd(file->name, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		file->fd = KO;
	}
	else
	{
		file->fd = open(file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file->fd == -1)
			return (ft_putstr_fd(OUTFILE_ERROR_FD, STDERR_FILENO));
		file->is_open = OK;
	}
}
