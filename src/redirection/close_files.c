/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:29:53 by phwang            #+#    #+#             */
/*   Updated: 2024/09/20 19:41:18 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_all_files(t_file *files)
{
	int	i;

	i = -1;
	if (!files)
		return ;
	while (files[++i].name)
	{
		if (files[i].is_open == OK)
			close_one_fd(files[i].fd);
		files[i].is_open = KO;
	}
}

void	close_one_fd(int fd)
{
	if (fd > -1)
		if (close(fd) < 0)
			perror(CLOSE_ERR);
}
