/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_tab_create.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 19:53:54 by phwang            #+#    #+#             */
/*   Updated: 2024/09/10 22:05:04 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	load_file_tab(t_data *minishell, char **dico_files)
{
	int	i;

	minishell->files = ft_calloc(minishell->nb_files + 1, sizeof(t_file));
	if (!minishell->files)
	{
		free_double_char(&dico_files);
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	}
	i = -1;
	while (dico_files[++i])
	{
		minishell->files[i].name = ft_strdup(dico_files[i]);
		if (!minishell->files[i].name)
		{
			free_double_char(&dico_files);
			return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
		}
	}
	free_double_char(&dico_files);
	return (OK);
}

int	load_files_type(t_data *minishell, t_list *token)
{
	t_list	*tmp_head;
	int		tab;

	tab = 0;
	tmp_head = token;
	while (tmp_head)
	{
		if (((t_token *)tmp_head->content)->type == INFILE_TYPE
			|| ((t_token *)tmp_head->content)->type == OUTFILE_TYPE
			|| ((t_token *)tmp_head->content)->type == APPEND_FILE_TYPE
			|| ((t_token *)tmp_head->content)->type == HD_LIMITER_TYPE)
		{
			minishell->files[tab].is_open = KO;
			minishell->files[tab++].type = ((t_token *)tmp_head->content)->type;
		}
		if (tmp_head->next == NULL)
			break ;
		tmp_head = tmp_head->next;
	}
	return (OK);
}
