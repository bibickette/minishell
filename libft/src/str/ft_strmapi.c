/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:39:02 by phwang            #+#    #+#             */
/*   Updated: 2024/03/16 20:19:14 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ntab;

	i = 0;
	ntab = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ntab)
		return (NULL);
	while (s[i])
	{
		ntab[i] = s[i];
		ntab[i] = f(i, s[i]);
		i++;
	}
	ntab[i] = '\0';
	return (ntab);
}
/*
applique la fonction f sur chaque char de la *s
creer un tableau avec les nouveaux char 
utiliser la fonction (*f)(bla, bla) en ecrivant f(blo, blo)
*/