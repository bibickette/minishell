/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:38:05 by phwang            #+#    #+#             */
/*   Updated: 2024/03/16 20:19:02 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*ps;

	ps = (unsigned char *) s;
	i = 0;
	while (i < n)
	{
		if (ps[i] == (unsigned char) c)
			return (ps + i);
		i++;
	}
	return (NULL);
}
/* dans la string *s 
cherche le int c (interprété comme un char) 
dans une longueur n
renvoie la string à partir de la premiere occurence de c 
mem signifie memoryBlock 
donc un pointeur vers une adresse mémoire */