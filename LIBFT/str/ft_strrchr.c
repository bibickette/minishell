/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 14:38:34 by phwang            #+#    #+#             */
/*   Updated: 2024/03/16 20:19:16 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ps;

	i = ft_strlen(s);
	ps = (char *) s;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return (ps + i);
		i--;
	}
	return (NULL);
}
/* dans une string *s cherche la dernière occurence c
renvoie un pointeur d'à partir de cette dernière */