/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countwords.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 17:46:30 by phwang            #+#    #+#             */
/*   Updated: 2024/08/25 17:46:36 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

int	countwords(const char *str, char sep)
{
	int	words;
	int	i;
	int	len;

	if (!str || !sep || ft_strlen(str) == 0)
		return (0);
	len = ft_strlen(str);
	i = -1;
	words = 0;
	if (str[0] != sep)
		words = 1;
	while (++i < len)
		if (str[i] == sep)
			if (str[i + 1] != sep && str[i + 1] != '\0')
				words++;
	return (words);
}
