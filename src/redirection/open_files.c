/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 16:36:12 by phwang            #+#    #+#             */
/*   Updated: 2024/09/13 16:40:50 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_all_files(t_data *minishell)
{
	int i;
	
	i = -1;
	while (++i < minishell->nb_files)
		if (open_all_infile(minishell, &minishell->files[i]) == KO
			|| open_all_outfile(&minishell->files[i]) == KO)
			return (KO);
	return (OK);
}
