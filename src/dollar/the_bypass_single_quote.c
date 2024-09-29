/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   the_bypass_single_quote.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexplor <hexplor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:20:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/29 18:43:34 by hexplor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*custom_return(char **var, char **stash, \
						char **new_expanded, char **expanded)
{
	if (stash != NULL)
	{
		the_bypass(var, stash, new_expanded, expanded);
		return (*new_expanded);
	}
	return (*expanded);
}

void	the_bypass(char **var, char **stash, \
						char **new_expanded, char **expanded)
{
	static int	flux;

	if (flux == 0)
	{
		if (ft_strchr_custom(*var, 39) != -1)
		{
			*stash = ft_strchr(*var, 39);
			*stash = ft_strdup(*stash);
			*var = ft_substr(*var, 0, ft_strchr_custom(*var, 39));
			flux++;
		}
	}
	else
	{
		*new_expanded = ft_strjoin(*expanded, *stash);
		free(*stash);
		free(*expanded);
		free(*var);
		printf("new_expanded: %s\n", *new_expanded);
		flux = 0;
	}
}
