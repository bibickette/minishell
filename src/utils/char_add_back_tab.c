/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_add_back_tab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 16:21:48 by phwang            #+#    #+#             */
/*   Updated: 2024/09/10 22:04:34 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	no_original_tab(char ***original_tab, char *to_add, char ***new_tab)
{
	if (!(*original_tab))
	{
		*new_tab = ft_calloc(2, sizeof(char *));
		if (!new_tab)
			return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
		(*new_tab)[0] = ft_strdup(to_add);
		if (!(*new_tab)[0])
		{
			free_double_char(original_tab);
			*original_tab = NULL;
			return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
		}
		(*new_tab)[1] = NULL;
		(*original_tab) = (*new_tab);
		return (OK);
	}
	return (OK);
}

int	count_n_copy_original_tab(char ***original_tab, char ***new_tab,
		int *nb_tab)
{
	(*nb_tab) = 0;
	while ((*original_tab)[(*nb_tab)])
		(*nb_tab)++;
	(*new_tab) = ft_calloc((*nb_tab) + 2, sizeof(char *));
	if (!new_tab)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	(*nb_tab) = -1;
	while ((*original_tab)[++(*nb_tab)])
	{
		(*new_tab)[(*nb_tab)] = ft_strdup((*original_tab)[(*nb_tab)]);
		if (!(*new_tab)[(*nb_tab)])
		{
			free_double_char(original_tab);
			*original_tab = NULL;
			return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
		}
	}
	return (OK);
}

int	char_add_back_tab(char ***original_tab, char *to_add)
{
	int		nb_tab;
	char	**new_tab;

	new_tab = NULL;
	if (!(*original_tab))
		return (no_original_tab(original_tab, to_add, &new_tab));
	if (count_n_copy_original_tab(original_tab, &new_tab, &nb_tab) == KO)
		return (KO);
	if (to_add)
	{
		new_tab[nb_tab] = ft_strdup(to_add);
		if (!new_tab[nb_tab])
		{
			free_double_char(original_tab);
			*original_tab = NULL;
			return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
		}
		nb_tab++;
	}
	new_tab[nb_tab] = NULL;
	free_double_char(original_tab);
	(*original_tab) = new_tab;
	return (OK);
}
