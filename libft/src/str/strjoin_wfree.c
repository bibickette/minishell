/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin_wfree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <phwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 22:11:16 by phwang            #+#    #+#             */
/*   Updated: 2026/01/22 18:23:27 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

char	*heedz_join(char *str, char *backup, char *buffer)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (backup[++i])
		str[i] = backup[i];
	while (buffer[j])
		str[i++] = buffer[j++];
	str[i] = '\0';
	return (str);
}

char	*strjoin_wfree(char *backup, char *buffer)
{
	char	*str;

	if (!backup)
	{
		backup = malloc(1 * sizeof(char));
		backup[0] = '\0';
	}
	if (!backup || !buffer)
	{
		if (backup)
			free(backup);
		return (0);
	}
	str = malloc(sizeof(char) * ((ft_strlen(backup) + ft_strlen(buffer)) + 1));
	if (!str)
	{
		if (backup)
			free(backup);
		return (0);
	}
	str = heedz_join(str, backup, buffer);
	free(backup);
	return (str);
}
