/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 17:45:51 by phwang            #+#    #+#             */
/*   Updated: 2024/03/16 20:21:02 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ntab;

	if (nmemb && (nmemb * size) / nmemb != size)
		return (NULL);
	ntab = malloc(nmemb * size);
	if (!ntab)
		return (NULL);
	ft_bzero(ntab, nmemb * size);
	return (ntab);
}
/*
(nmemb * size) / nmemb != size
en fait on vérifie si nmemb * size rentre dans un size_t
s'il est trop grand il faussera le resultat de la multiplication
donc lorsqu'il se divisera à nouveau, on aura pas le size du départ
donc c'est overflow, NULL */