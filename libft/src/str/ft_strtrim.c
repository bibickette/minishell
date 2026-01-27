/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/15 14:32:03 by phwang            #+#    #+#             */
/*   Updated: 2024/03/16 20:19:16 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	cutend(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	lenmax;
	int	len;
	int	lenb;

	i = 0;
	len = 0;
	lenmax = ft_strlen(s1);
	while (s1[lenmax - 1 - i] && i < lenmax)
	{
		j = 0;
		lenb = len;
		while (set[j])
		{
			if (set[j] == s1[lenmax - 1 - i])
				len++;
			j++;
		}
		if (lenb == len)
			break ;
		i++;
	}
	return (len);
}

static void	cutbeg(char const **s1, char const *set)
{
	int	j;
	int	i;
	int	len;

	len = 0;
	i = 0;
	j = 0;
	while (set[j])
	{
		if (set[j] == (*s1)[i])
		{
			j = -1;
			len++;
			i++;
		}
		j++;
	}
	(*s1) += len;
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char		*ntab;
	size_t		sizeend;
	size_t		j;

	j = 0;
	if ((!set) || (!s1))
		return (NULL);
	cutbeg(&s1, set);
	sizeend = cutend(s1, set);
	ntab = malloc((ft_strlen(s1) - sizeend + 1) * sizeof(char));
	if (!ntab)
		return (NULL);
	while (j < ft_strlen(s1) - sizeend)
	{
		ntab[j] = s1[j];
		j++;
	}
	ntab[j] = '\0';
	return (ntab);
}
/*
enleve les char de set dans s1
*/