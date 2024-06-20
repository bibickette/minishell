/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:42:23 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/20 21:22:32 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	Renvoie la taille de la chaine de caractère s
*/

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
