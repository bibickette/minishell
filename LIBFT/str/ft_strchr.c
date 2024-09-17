/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:38:20 by phwang            #+#    #+#             */
/*   Updated: 2024/03/16 20:19:09 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strchr(const char *s, int c)
{
	int			i;
	char		*ps;

	i = 0;
	ps = (char *) s;
	if (ps[i] == '\0')
		return (ps);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (ps + i);
		i++;
	}
	if (s[i] == (char)c)
		return (ps + i);
	return (NULL);
}
/* dans une str *s cherche la première occurence c
renvoie un pointeur sur *s de la première occurence c
last if is for checking if the int c is \0*/