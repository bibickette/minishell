/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:40:02 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/20 21:22:30 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Affiche la chaine de caractère s sur le file descriptor fd
*/

void	ft_putstr_fd(const char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
