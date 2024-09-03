/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 15:51:27 by phwang            #+#    #+#             */
/*   Updated: 2024/03/16 20:19:09 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*ft_strdup(const char *s)
{
	char	*sdup;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	sdup = (char *) malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!(sdup))
		return (NULL);
	while (s[i])
	{
		sdup[i] = s[i];
		i++;
	}
	sdup[i] = '\0';
	return (sdup);
}
