/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <phwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:48:41 by phwang            #+#    #+#             */
/*   Updated: 2026/01/27 18:16:52 by phwang           ###   ########.fr       */
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
	if (set_node(tmp, minishell, &i) == KO)
		return (KO);
	minishell->nb_cmd = i + 1;
	tmp = token;
	if (fill_cmd_list(minishell, tmp) == KO)
		return (KO);
	tmp = token;
	return (fill_cmd_files_list(minishell, tmp));
}

int	add_t_cmd_back(t_data *minishell, int index)
{
	t_cmd	*new_cmd;
	t_list	*new;

	new_cmd = ft_calloc(1, sizeof(t_cmd));
	if (!new_cmd)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	new_cmd->index = index;
	new = ft_lstnew(new_cmd);
	if (!new)
	{
		free(new_cmd);
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	}
	ft_lstadd_back(&minishell->list_cmd, new);
	return (OK);
}

int	fill_cmd_list(t_data *minishell, t_list *tmp)
{
	t_list	*tmp_cmd_list;

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

int	set_node(t_list *tmp, t_data *minishell, int *i)
{
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == PIPE_TYPE)
		{
			(*i)++;
			if (add_t_cmd_back(minishell, *i) == KO)
			{
				minishell->last_status = 1;
				return (KO);
			}
		}
		tmp = tmp->next;
	}
	return (OK);
}
