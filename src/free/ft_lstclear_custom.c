/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_custom.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 23:46:08 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/20 20:15:13 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_lstclear_custom(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_token	*token;

	tmp = *lst;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		del(token->str);
		tmp = tmp->next;
	}
	ft_lstclear_libft(lst, del);
	free(*lst);
}

void	ft_lstclear_custom_cmd(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_cmd	*cmd;

	tmp = *lst;
	if (!tmp)
		return ;
	while (tmp)
	{
		cmd = (t_cmd *)tmp->content;
		del(cmd->cmd);
		cmd->cmd = 0;
		if (cmd->cmd_args)
			free_double_char(&cmd->cmd_args);
		if (cmd->nb_files > 0)
			free_files_tab_cmd(cmd, cmd->files);
		tmp = tmp->next;
	}
	ft_lstclear_libft(lst, del);
	free(*lst);
	*lst = 0;
}
