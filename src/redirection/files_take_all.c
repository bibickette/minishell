/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_take_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:20:00 by phwang            #+#    #+#             */
/*   Updated: 2024/09/06 19:54:33 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	take_all_files(t_data *minishell, t_list *token)
{
	if (count_n_allocate_files(minishell, token) == KO)
		return (KO);
	load_files_type(minishell, token);
	if (!minishell->files || !minishell->files[0].name)
		return (KO);
	return (OK);
}

int	count_n_allocate_files(t_data *minishell, t_list *token)
{
	t_list	*tmp_head;
	char	**dico_files;

	tmp_head = token;
	dico_files = 0;
	minishell->nb_files = 0;
	while (tmp_head)
	{
		if (file_type(tmp_head) == OK)
		{
			char_add_back_tab(&dico_files, ((t_token *)tmp_head->content)->str);
			minishell->nb_files++;
		}
		if (tmp_head->next == NULL)
			break ;
		tmp_head = tmp_head->next;
	}
	if (minishell->nb_files == 0 || !dico_files)
		return (KO);
	return (load_file_tab(minishell, dico_files));
}

int	file_type(t_list *tmp_head)
{
	if (((t_token *)tmp_head->content)->type == INFILE_TYPE
		|| ((t_token *)tmp_head->content)->type == OUTFILE_TYPE
		|| ((t_token *)tmp_head->content)->type == APPEND_FILE_TYPE
		|| ((t_token *)tmp_head->content)->type == HD_LIMITER_TYPE)
		return (OK);
	return (KO);
}
