/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_w_space.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:52:51 by phwang            #+#    #+#             */
/*   Updated: 2024/09/22 14:09:33 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	countwords_wsp(const char *str)
{
	int	words;
	int	i;
	int	len;

	if (!str || ft_strlen(str) == 0)
		return (0);
	len = ft_strlen(str);
	i = -1;
	words = 1;
	while (++i < len)
	{
		if (ft_is_white_space(str[i]) == 1 && ft_is_white_space(str[i + 1]) != 1
			&& str[i + 1] != '\0')
			words++;
		if (ft_is_white_space(str[i]) == 0 && ft_is_white_space(str[i + 1]) != 0
			&& str[i + 1] != '\0')
			words++;
	}
	return (words);
}

static void	free_tab(char ***tab, int pos)
{
	while (pos >= 0)
	{
		free((*tab)[pos]);
		(*tab)[pos] = NULL;
		pos--;
	}
	free(*tab);
	*tab = NULL;
}

static void	count_len(char *str, int *index, int *len)
{
	if (ft_is_white_space(str[(*index)]) == 1)
	{
		while (ft_is_white_space(str[(*index)]) == 1)
		{
			(*index)++;
			(*len)++;
		}
	}
	else
	{
		while (ft_is_white_space(str[(*index)]) == 0 && str[(*index)])
		{
			(*index)++;
			(*len)++;
		}
	}
}

int	create_tab(char ***tab, char *str, int *index, int word_nb)
{
	int	len;
	int	i;

	len = 0;
	count_len(str, index, &len);
	(*tab)[word_nb] = malloc((len + 1) * sizeof(char));
	if (!(*tab)[word_nb])
		return (free_tab(tab, word_nb), KO);
	(*tab)[word_nb][len] = '\0';
	i = -1;
	while (++i < len)
		(*tab)[word_nb][i] = str[(*index) - len + i];
	return (OK);
}

char	**split_w_space(char *s)
{
	char	**tab;
	int		words;
	int		i;
	int		index;

	if (!s)
		return (NULL);
	words = countwords_wsp(s);
	tab = malloc((words + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	i = -1;
	index = 0;
	while (++i < words)
		if (create_tab(&tab, s, &index, i) == KO)
			return (NULL);
	tab[i] = NULL;
	return (tab);
}
