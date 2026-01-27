/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_toktype_precise.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 22:13:30 by phwang            #+#    #+#             */
/*   Updated: 2024/09/29 17:01:39 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_builtin_type(t_token *current)
{
	if (is_builtin(current->str) == OK)
	{
		current->type = BUILTIN_TYPE;
		if (ft_strncmp(current->str, "echo", ft_strlen(current->str)) == 0
			|| ft_strncmp(current->str, "exit", ft_strlen(current->str)) == 0)
			current->builtin_type = BUILT_W_OPT;
		else if ((ft_strncmp(current->str, "env",
					ft_strlen(current->str)) == 0))
			current->builtin_type = BUILT_NO_OPT_ARG;
		else
			current->builtin_type = BUILT_NO_OPTION;
	}
}

void	reset_operator_type(t_token *current)
{
	if (check_operator(current->str) == OK)
	{
		if (current->str[0] == '|')
			current->type = PIPE_TYPE;
		else if (ft_strcmp(current->str, "<<") == 0)
			current->type = HERE_DOC_TYPE;
		else if (ft_strcmp(current->str, ">>") == 0)
			current->type = HD_APPEND_TYPE;
		else if (ft_strcmp(current->str, ">") == 0)
			current->type = OUT_REDIR_TYPE;
		else if (ft_strcmp(current->str, "<") == 0)
			current->type = IN_REDIR_TYPE;
	}
}

void	reset_every_first_cmd(t_list *tmp)
{
	int	cmd;

	cmd = KO;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == WORD_TYPE)
			((t_token *)tmp->content)->type = CMD_TYPE;
		if (((t_token *)tmp->content)->type == CMD_TYPE
			|| ((t_token *)tmp->content)->type == BUILTIN_TYPE)
			cmd = OK;
		if ((((t_token *)tmp->content)->type == OPT_TYPE
				|| ((t_token *)tmp->content)->type == ARG_TYPE) && cmd == KO)
		{
			((t_token *)tmp->content)->type = CMD_TYPE;
			cmd = OK;
		}
		if (((t_token *)tmp->content)->type == PIPE_TYPE)
			cmd = KO;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}
