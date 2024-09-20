/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_take_all.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 14:20:00 by phwang            #+#    #+#             */
/*   Updated: 2024/09/20 19:44:34 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	take_all_hd_files(t_data *minishell, t_list *token)
{
	if (count_n_allocate_files(minishell, token) == KO)
		return (KO);
	load_files_type(minishell, token);
	return (OK);
}

int	count_n_allocate_files(t_data *minishell, t_list *token)
{
	t_list	*tmp_head;
	char	**dico_files;

	tmp_head = token;
	dico_files = 0;
	minishell->nb_hd_files = 0;
	while (tmp_head)
	{
		if (file_type(tmp_head) == OK)
		{
			char_add_back_tab(&dico_files, \
			((t_token *)tmp_head->content)->str);
			minishell->nb_hd_files++;
		}
		if (tmp_head->next == NULL)
			break ;
		tmp_head = tmp_head->next;
	}
	if (minishell->nb_hd_files == 0 || !dico_files)
		return (OK);
	return (load_file_tab(minishell, dico_files));
}

int	file_type(t_list *tmp_head)
{
	if (((t_token *)tmp_head->content)->type == HD_LIMITER_TYPE)
		return (OK);
	return (KO);
}

int	load_file_tab(t_data *minishell, char **dico_files)
{
	int	i;

	minishell->files = \
	ft_calloc(minishell->nb_hd_files + 1, sizeof(t_file));
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

void	load_files_type(t_data *minishell, t_list *token)
{
	t_list	*tmp_head;
	int		tab;
	int		index_cmd;

	index_cmd = 0;
	tab = 0;
	tmp_head = token;
	while (tmp_head)
	{
		if (((t_token *)tmp_head->content)->type == PIPE_TYPE)
			index_cmd++;
		if (file_type(tmp_head) == OK)
		{
			minishell->files[tab].index = tab;
			minishell->files[tab].index_cmd = index_cmd;
			minishell->files[tab].is_open = KO;
			minishell->files[tab++].type = \
			((t_token *)tmp_head->content)->type;
		}
		if (tmp_head->next == NULL)
			break ;
		tmp_head = tmp_head->next;
	}
}
