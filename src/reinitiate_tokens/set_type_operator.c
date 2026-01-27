/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_type_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:18:02 by phwang            #+#    #+#             */
/*   Updated: 2024/09/20 17:54:43 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_type_operator(t_token *last_token)
{
	if (last_token->str[0] == '|')
		last_token->type = PIPE_TYPE;
	else if (ft_strcmp(last_token->str, "<<") == 0)
		last_token->type = HERE_DOC_TYPE;
	else if (ft_strcmp(last_token->str, ">>") == 0)
		last_token->type = HD_APPEND_TYPE;
	else if (ft_strcmp(last_token->str, ">") == 0)
		last_token->type = OUT_REDIR_TYPE;
	else if (ft_strcmp(last_token->str, "<") == 0)
		last_token->type = IN_REDIR_TYPE;
}

void	reset_cmd_pipe(t_list *head)
{
	int		on_pipe_nb;
	int		cmd_on_pipe;
	t_list	*tmp;

	on_pipe_nb = 0;
	cmd_on_pipe = 0;
	tmp = head;
	while (tmp)
	{
		if (is_cd(tmp) == OK)
			return ;
		reset_cmd_pipe_type(tmp, &cmd_on_pipe, &on_pipe_nb);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	tmp = head;
}

void	reset_cmd_pipe_type(t_list *current, int *cmd_on_pipe, int *on_pipe_nb)
{
	if (((t_token *)current->content)->type == CMD_TYPE
		|| ((t_token *)current->content)->type == BUILTIN_TYPE)
		(*cmd_on_pipe)++;
	if (((t_token *)current->content)->type == PIPE_TYPE)
		(*on_pipe_nb)++;
	if (((t_token *)current->content)->type == WORD_TYPE
		&& cmd_on_pipe == on_pipe_nb)
	{
		((t_token *)current->content)->type = CMD_TYPE;
		set_builtin_type((t_token *)current->content);
		(*cmd_on_pipe)++;
	}
	else if (((t_token *)current->content)->type == WORD_TYPE
		&& (*cmd_on_pipe) == 0)
	{
		((t_token *)current->content)->type = CMD_TYPE;
		set_builtin_type((t_token *)current->content);
	}
	else if (((t_token *)current->content)->type == WORD_TYPE
		&& (*cmd_on_pipe) == (*on_pipe_nb) + 1)
		((t_token *)current->content)->type = ARG_TYPE;
}

int	is_cd(t_list *tmp)
{
	if ((((t_token *)tmp->content)->type == BUILTIN_TYPE)
		&& ft_strcmp(((t_token *)tmp->content)->str, "cd") == 0)
	{
		if (tmp->next == NULL)
			return (OK);
		tmp = tmp->next;
		if (((t_token *)tmp->content)->str[0] == '-'
			&& ft_strlen(((t_token *)tmp->content)->str) == 1)
			((t_token *)tmp->content)->type = ARG_TYPE;
	}
	return (KO);
}
