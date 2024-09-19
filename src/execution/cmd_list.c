/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:48:41 by phwang            #+#    #+#             */
/*   Updated: 2024/09/19 17:16:55 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_cmd_list(t_data *minishell, t_list *token)
{
	t_list	*tmp;
	int		i;

	i = 0;
	tmp = token;
	if (add_t_cmd_back(minishell, i) == KO)
		return (KO);
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == PIPE_TYPE)
		{
			i++;
			if (add_t_cmd_back(minishell, i) == KO)
				return (KO);
		}
		tmp = tmp->next;
	}
	fill_cmd_list(minishell, token);
	return (OK);
}

int	add_t_cmd_back(t_data *minishell, int index)
{
	t_cmd	*new_cmd;
	t_list	*new;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	new_cmd->index = index;
	new = ft_lstnew_libft(new_cmd);
	if (!new)
	{
		free(new_cmd);
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	}
	ft_lstadd_back_libft(&minishell->list_cmd, new);
	return (OK);
}

int	fill_cmd_list(t_data *minishell, t_list *token)
{
	t_list	*tmp;
	t_list	*tmp_cmd_list;

	tmp = token;
	tmp_cmd_list = minishell->list_cmd;
	while (tmp)
	{
		if (fill_cmd_node(tmp, tmp_cmd_list) == KO)
			return (KO);
		if (((t_token *)tmp->content)->type == PIPE_TYPE)
			tmp_cmd_list = tmp_cmd_list->next;
		tmp = tmp->next;
	}
	return (OK);
}

int	fill_cmd_node(t_list *tmp, t_list *tmp_cmd_list)
{
	if (((t_token *)tmp->content)->type == CMD_TYPE
		|| ((t_token *)tmp->content)->type == BUILTIN_TYPE)
	{
		if (((t_token *)tmp->content)->type == CMD_TYPE)
			((t_cmd *)tmp_cmd_list->content)->cmd_type = CMD_TYPE;
		else
			((t_cmd *)tmp_cmd_list->content)->cmd_type = BUILTIN_TYPE;
		if (char_add_back_tab(&((t_cmd *)tmp_cmd_list->content)->cmd_args,
				((t_token *)tmp->content)->str) == KO)
			return (KO);
		((t_cmd *)tmp_cmd_list->content)->cmd = ft_strdup(((t_token *)tmp->content)->str);
		if (!((t_cmd *)tmp_cmd_list->content)->cmd)
			return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	}
	else if (((t_token *)tmp->content)->type == ARG_TYPE
		|| ((t_token *)tmp->content)->type == OPT_TYPE)
	{
		if (char_add_back_tab(&((t_cmd *)tmp_cmd_list->content)->cmd_args,
				((t_token *)tmp->content)->str) == KO)
			return (KO);
	}
	if (((t_token *)tmp->content)->type == INFILE_TYPE
		|| ((t_token *)tmp->content)->type == OUTFILE_TYPE
		|| ((t_token *)tmp->content)->type == APPEND_FILE_TYPE
		|| ((t_token *)tmp->content)->type == HD_LIMITER_TYPE)
		((t_cmd *)tmp_cmd_list->content)->nb_files++;
	return (OK);
}
