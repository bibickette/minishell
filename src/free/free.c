/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 00:15:48 by phwang            #+#    #+#             */
/*   Updated: 2024/07/08 17:46:48 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	que fait cette fonction ?
*/
void	apocalypse(t_data *minishell)
{
	get_next_line(STDIN_FILENO, 1);
	if(minishell->path)
		free_double_char(minishell->path);
	minishell->path = 0;
	if(minishell->token)
		free(minishell->token);
	minishell->token = 0;
	if(minishell->builtins)
		free(minishell->builtins);
	minishell->builtins = 0;
	if(minishell)
		free(minishell);
	minishell = 0;
	return ;
}
