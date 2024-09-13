/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_files.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 18:29:53 by phwang            #+#    #+#             */
/*   Updated: 2024/09/13 17:33:20 by phwang           ###   ########.fr       */
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
		if(files[i].is_open == OK)
			close_one_fd(files[i].fd);
		files[i].is_open = KO;
	}
}

void	close_one_fd(int fd)
{
	if(fd > -1)
		if (close(fd) < 0)
			perror(CLOSE_ERR);
}

void	print_all_files(t_file *files)
{
	int	i;

	i = -1;
	if (!files)
		return ;
	while (files[++i].name)
	{
		printf("file name : %s\n", files[i].name);
		printf("file type : %d\n", files[i].type);
		printf("file is open : %d\n", files[i].is_open);
		printf("file fd open : %d\n", files[i].fd);
	}
}
