/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:38:32 by phwang            #+#    #+#             */
/*   Updated: 2024/03/16 20:19:15 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	size_t		i;
	size_t		j;
	char		*ps1;

	i = 0;
	j = 0;
	ps1 = (char *) s1;
	if (s2[i] == '\0')
		return (ps1);
	while (s1[i] && i < len)
	{
		j = 0;
		while ((s1[i + j]) && (s2[j])
			&& (s1[i + j] == s2[j]) && (i + j < len))
		{
			if (s2[j + 1] == '\0')
				return (ps1 + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
/* recherche dans une longueur n sur *s1 la str *s2
la différence avec strstr :
ça recherche dans une longueur n et non toute la str *s1 */