/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:29:10 by phwang            #+#    #+#             */
/*   Updated: 2024/03/16 20:19:17 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*ntab;
	size_t		i;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
		return (ft_strdup(""));
	i = ft_strlen(s + start);
	if (len > i)
		len = i;
	ntab = malloc((len + 1) * sizeof(char));
	if (!ntab)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		ntab[i] = s[start + i];
		i++;
	}
	ntab[i] = '\0';
	return (ntab);
}
/* dans une str *s, va a l'index start donc le numero de l'indice
renvoie une nouvelle str a partir de cet index
len est la longueur maximum de la nouvelle str */