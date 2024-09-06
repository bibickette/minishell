/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:21:33 by phwang            #+#    #+#             */
/*   Updated: 2024/09/06 18:53:05 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_all_infile(t_data *minishell, t_file *file)
{
	if (file->type == INFILE_TYPE || file->type == HD_LIMITER_TYPE)
	{
		if (file->type == HD_LIMITER_TYPE)
		{
			heredoc_create(minishell, file->name);
			file->name = HERE_DOC;
		}
		if (open_infile(file) == KO)
			return (KO);
	}
	return (OK);
}

int	open_all_outfile(t_file *file)
{
	if (file->type == OUTFILE_TYPE)
	{
		if (open_outfile(file) == KO)
			return (KO);
	}
	else if (file->type == APPEND_FILE_TYPE)
		if (open_append_outfile(file) == KO)
			return (KO);
	return (OK);
}

int	open_infile(t_file *file)
{
	if ((access(file->name, F_OK) == 0) && (access(file->name, R_OK) == 0))
	{
		file->fd = open(file->name, O_RDONLY);
		if (file->fd == -1)
			return (ft_putstr_fd(INFILE_ERROR_FD, STDERR_FILENO), KO);
		file->is_open = OK;
		return (OK);
	}
	else if ((access(file->name, F_OK) == 0) && (access(file->name, R_OK) != 0))
	{
		perror(FILE_ERR);
		ft_putstr_fd("File error : ", STDERR_FILENO);
		ft_putstr_fd(file->name, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		file->fd = KO;
		return (KO);
	}
	else
	{
		file->fd = KO;
		return (ft_putstr_fd(FILE_NOT_EXIST, STDERR_FILENO), KO);
	}
	return (OK);
}

int	open_outfile(t_file *file)
{
	if ((access(file->name, F_OK) == 0) && (access(file->name, W_OK) != 0))
	{
		perror(FILE_ERR);
		ft_putstr_fd("File error : ", STDERR_FILENO);
		ft_putstr_fd(file->name, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		file->fd = KO;
		return (KO);
	}
	else
	{
		file->fd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file->fd == -1)
			return (ft_putstr_fd(OUTFILE_ERROR_FD, STDERR_FILENO), KO);
		file->is_open = OK;
		return (OK);
	}
	return (OK);
}

int	open_append_outfile(t_file *file)
{
	if ((access(file->name, F_OK) == 0) && (access(file->name, W_OK) != 0))
	{
		perror(FILE_ERR);
		ft_putstr_fd("File error : ", STDERR_FILENO);
		ft_putstr_fd(file->name, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
		file->fd = KO;
		return (KO);
	}
	else
	{
		file->fd = open(file->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (file->fd == -1)
			return (ft_putstr_fd(OUTFILE_ERROR_FD, STDERR_FILENO), KO);
		file->is_open = OK;
		return (OK);
	}
	return (OK);
}
