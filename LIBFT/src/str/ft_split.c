/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 14:22:20 by phwang            #+#    #+#             */
/*   Updated: 2024/05/27 23:15:52 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"

static int	countwords(const char *str, char sep)
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

static char	**free_tab(char **tab, int pos)
{
	while (pos >= 0)
	{
		free(tab[pos]);
		pos--;
	}
	free(tab);
	return (NULL);
}

static char	**fill_fill(char **tab, int pos, char const **s, int j)
{
	int	n;

	n = 0;
	while (n < j)
	{
		tab[pos][n] = **s;
		n++;
		(*s)++;
	}
	tab[pos][n] = '\0';
	return (tab);
}

static char	**fill_tab(char **tab, int pos, char const *s, char sep)
{
	int	j;

	j = 0;
	while (*s == sep)
		s++;
	while (*(s + j) != sep && *(s + j) != '\0')
		j++;
	if (j == 0)
		return (tab);
	tab[pos] = malloc((j + 1) * sizeof(char));
	if (!tab[pos])
	{
		tab[pos] = NULL;
		return (tab);
	}
	tab = fill_fill(tab, pos, &s, j);
	if (*s == '\0')
		return (tab);
	return (fill_tab(tab, pos + 1, s, sep));
}

char	**ft_split(char const *s, char c)
{
	char	**ntab;
	int		size;
	int		pos;
	int		i;

	i = 0;
	pos = 0;
	size = countwords(s, c);
	ntab = malloc((size + 1) * sizeof(char *));
	if (!ntab)
		return (NULL);
	if (size == 0)
	{
		ntab[0] = NULL;
		return (ntab);
	}
	ntab = fill_tab(ntab, pos, s, c);
	while (i < size)
	{
		if (ntab[i] == NULL)
			return (free_tab(ntab, i));
		i++;
	}
	ntab[size] = 0;
	return (ntab);
}