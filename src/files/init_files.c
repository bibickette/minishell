/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:53:11 by phwang            #+#    #+#             */
/*   Updated: 2024/09/20 21:41:30 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fill_cmd_node(t_list *tmp, t_list *tmp_cmd_list)
{
	if (((t_token *)tmp->content)->type == CMD_TYPE
		|| ((t_token *)tmp->content)->type == BUILTIN_TYPE)
	{
		((t_cmd *)tmp_cmd_list->content)->cmd_type = \
		((t_token *)tmp->content)->type;
		if (char_add_back_tab(&((t_cmd *)tmp_cmd_list->content)->cmd_args,
				((t_token *)tmp->content)->str) == KO)
			return (KO);
		((t_cmd *)tmp_cmd_list->content)->cmd = \
		ft_strdup(((t_token *)tmp->content)->str);
		if (!((t_cmd *)tmp_cmd_list->content)->cmd)
			return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	}
	if (((t_token *)tmp->content)->type == ARG_TYPE
		|| ((t_token *)tmp->content)->type == OPT_TYPE || \
		((t_token *)tmp->content)->type == NO_TYPE)
	{
		if (char_add_back_tab(&((t_cmd *)tmp_cmd_list->content)->cmd_args,
				((t_token *)tmp->content)->str) == KO)
			return (KO);
	}
	if (is_not_hd(tmp) == OK)
		((t_cmd *)tmp_cmd_list->content)->nb_files++;
	return (OK);
}

int	fill_cmd_files_list(t_data *minishell, t_list *tmp)
{
	t_list	*cmd_list;
	int		i;

	i = 0;
	cmd_list = minishell->list_cmd;
	while (tmp)
	{
		if (init_files(cmd_list) == KO)
			return (KO);
		if (is_not_hd(tmp) == OK)
			if (set_file(cmd_list, tmp, &i) == KO)
				return (KO);
		if (((t_token *)tmp->content)->type == PIPE_TYPE)
		{
			cmd_list = cmd_list->next;
			i = 0;
		}
		tmp = tmp->next;
	}
	return (OK);
}

int	is_not_hd(t_list *tmp)
{
	if (((t_token *)tmp->content)->type == INFILE_TYPE
		|| ((t_token *)tmp->content)->type == OUTFILE_TYPE
		|| ((t_token *)tmp->content)->type == APPEND_FILE_TYPE)
		return (OK);
	return (KO);
}

int	set_file(t_list *cmd_list, t_list *tmp, int *i)
{
	((t_cmd *)cmd_list->content)->files[*i].fd = KO;
	((t_cmd *)cmd_list->content)->files[*i].index = *i;
	((t_cmd *)cmd_list->content)->files[*i].index_cmd = KO;
	((t_cmd *)cmd_list->content)->files[*i].is_open = KO;
	((t_cmd *)cmd_list->content)->files[*i].type = \
	((t_token *)tmp->content)->type;
	((t_cmd *)cmd_list->content)->files[*i].name = \
	ft_strdup(((t_token *)tmp->content)->str);
	if (!((t_cmd *)cmd_list->content)->files[*i].name)
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	(*i)++;
	return (OK);
}

int	init_files(t_list *cmd_list)
{
	if (!((t_cmd *)cmd_list->content)->files
		&& ((t_cmd *)cmd_list->content)->nb_files > 0)
	{
		((t_cmd *)cmd_list->content)->files = \
		ft_calloc(((t_cmd *)cmd_list->content)->nb_files + 1, sizeof(t_file));
		if (!((t_cmd *)cmd_list->content)->files)
			return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	}
	return (OK);
}
