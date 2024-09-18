/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_tabs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:28:28 by phwang            #+#    #+#             */
/*   Updated: 2024/09/18 15:28:57 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	build_cmd_tab(t_data *minishell, t_list *token)
{
	int		i;
	t_list	*tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == PIPE_TYPE)
			i++;
		if (((t_token *)tmp->content)->type == CMD_TYPE
			|| ((t_token *)tmp->content)->type == BUILTIN_TYPE)
			if (put_in_cmd_tab(tmp, &minishell->cmd_original, i) == KO)
				return (KO);
		if (((t_token *)tmp->content)->type == CMD_TYPE
			|| ((t_token *)tmp->content)->type == BUILTIN_TYPE
			|| ((t_token *)tmp->content)->type == OPT_TYPE
			|| ((t_token *)tmp->content)->type == ARG_TYPE)
			if (put_in_cmd_tab(tmp, &minishell->command_tab, i) == KO)
				return (KO);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	minishell->nb_cmd = i + 1;
	return (OK);
}

int	put_in_cmd_tab(t_list *tmp, char ***cmd_tab, int i)
{
	char	*tmp_cmd;

	tmp_cmd = NULL;
	if (!(*cmd_tab) || !(*cmd_tab)[i])
	{
		if (char_add_back_tab(cmd_tab, ((t_token *)tmp->content)->str) == KO)
			return (KO);
	}
	else if ((*cmd_tab)[i])
	{
		tmp_cmd = ft_strjoin((*cmd_tab)[i], " ");
		if (!tmp_cmd)
			return (ft_putstr_fd(STRJOIN_ERR, STDOUT_FILENO), KO);
		free((*cmd_tab)[i]);
		(*cmd_tab)[i] = NULL;
		tmp_cmd = strjoin_wfree(tmp_cmd, ((t_token *)tmp->content)->str);
		if (!tmp_cmd)
			return (ft_putstr_fd(STRJOIN_ERR, STDOUT_FILENO), KO);
		(*cmd_tab)[i] = tmp_cmd;
	}
	return (OK);
}
