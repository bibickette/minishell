/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr_minish.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 18:02:20 by phwang            #+#    #+#             */
/*   Updated: 2024/09/10 20:33:34 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strnstr_minish(char *s1, char *s2, size_t len)
{
	size_t	i;
	size_t	j;
	char	*ps1;

	i = -1;
	j = 0;
	ps1 = (char *)s1;
	if (s2[0] == '\0')
		return (ps1);
	while (++i < len && s1[i])
	{
		j = 0;
		while ((s1[i + j]) && (s2[j]) && (s1[i + j] == s2[j]) && (i + j < len))
		{
			if ((s2[j + 1] == '\0' && (s1[i + j + 1] == '|' || s1[i + j
							+ 1] == '>' || s1[i + j + 1] == '<' || s1[i + j
							+ 1] == ' ' || s1[i + j + 1] == 34 || s1[i + j
							+ 1] == 39 || s1[i + j + 1] == '\0')) || (s2[j
						+ 1] == '\0' && (s2[j] == 34 || s2[j] == 39
						|| check_operator(s2) == OK)))
				return (ps1 + i);
			j++;
		}
	}
	return (NULL);
}
