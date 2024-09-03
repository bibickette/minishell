/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:30:18 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/02 20:05:50 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_fd(char *path)
{
	int	fd;

	fd = open(path, O_CREAT | O_TRUNC);
	if (fd == -1)
		printf("bad fd file\n");
	else
		printf("GOCHA\n");
	return (fd);
}
