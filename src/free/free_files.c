/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:45:48 by phwang            #+#    #+#             */
/*   Updated: 2024/09/20 20:15:33 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_files_tab(t_data *minishell, t_file *files)
{
	int	i;

	i = -1;
	if (!files || !minishell->nb_hd_files)
		return ;
	while (i < minishell->nb_hd_files && minishell->files[++i].name)
	{
		free(files[i].name);
		files[i].name = 0;
	}
	free(files);
	files = 0;
	minishell->nb_hd_files = 0;
}

void	free_files_tab_cmd(t_cmd *cmd, t_file *files)
{
	int	i;

	i = -1;
	if (!files || !cmd->nb_files)
		return ;
	while (i < cmd->nb_files && cmd->files[++i].name)
	{
		free(files[i].name);
		files[i].name = 0;
	}
	free(files);
	files = 0;
	cmd->nb_files = 0;
}
