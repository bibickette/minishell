/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 22:05:44 by phwang            #+#    #+#             */
/*   Updated: 2024/09/06 00:41:49 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int redirection_in(t_file *files)
{
	int i;
	i = -1;
	if(!files)
		return (OK);
	while(files[++i].name)
	{
		if(files[i].type == INFILE_TYPE || files[i].type == HD_LIMITER_TYPE)
		{
			if(files[i].fd != KO)
			{
				if (dup2(files[i].fd, STDIN_FILENO) < 0)
					return (perror(DUP_ERR), errno);
			}
			else
				return (KO);
		}
	}
	return (OK);
}

int redirection_out(t_file *files)
{
	int i;
	i = -1;
	if(!files)
		return (OK);
	while(files[++i].name)
	{
		if(files[i].type == OUTFILE_TYPE || files[i].type == APPEND_FILE_TYPE)
		{
			if(files[i].fd != KO)
			{
				if (dup2(files[i].fd, STDOUT_FILENO) < 0)
					return (perror(DUP_ERR), errno);
			}
			else
				return (KO);
		}
	}
	return (OK);
}
