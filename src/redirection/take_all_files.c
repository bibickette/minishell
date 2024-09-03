/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_all_files.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:20:00 by phwang            #+#    #+#             */
/*   Updated: 2024/09/03 14:13:39 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	take_all_files(t_data *minishell, t_list *token)
{
	int	i;

	if (count_n_allocate_files(minishell, token) == KO)
		return (KO);
	load_files_type(minishell, token);
	i = -1;
	if (!minishell->files || !minishell->files[0].name)
		return (KO);
	while(++i < minishell->nb_files)
		open_file(minishell, &minishell->files[i]);
	return (OK);
}

int	count_n_allocate_files(t_data *minishell, t_list *token)
{
	t_list	*tmp_head;
	char	**dico_files;
	int		i;

	tmp_head = token;
	dico_files = 0;
	minishell->nb_files = 0;
	while (tmp_head)
	{
		if (((t_token *)tmp_head->content)->type == INFILE_TYPE
			|| ((t_token *)tmp_head->content)->type == OUTFILE_TYPE
			|| ((t_token *)tmp_head->content)->type == APPEND_FILE_TYPE
			|| ((t_token *)tmp_head->content)->type == HD_LIMITER_TYPE)
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
	minishell->files = ft_calloc(minishell->nb_files + 1, sizeof(t_file));
	if (!minishell->files)
	{
		free_double_char(dico_files);
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	}
	i = -1;
	while (dico_files[++i])
	{
		minishell->files[i].name = ft_strdup(dico_files[i]);
		if (!minishell->files[i].name)
		{
			free_double_char(dico_files);
			return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
		}
	}
	free_double_char(dico_files);
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
