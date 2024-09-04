/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:01:03 by phwang            #+#    #+#             */
/*   Updated: 2024/09/04 23:02:18 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_token_type(t_list *head)
{
	t_token	*before;
	t_list	*current;
	t_list	*after;
	int		i;

	i = 0;
	before = NULL;
	current = head;
	after = NULL;
	while (current)
	{
		after = NULL;
		if (current->next)
			after = current->next;
		((t_token *)current->content)->index = i++;
		analyze_type((t_token *)current->content, before);
		if (after)
		{
			before = ((t_token *)current->content);
			current = after;
		}
		else
			return ;
	}
}

void	analyze_type(t_token *current, t_token *before)
{
	if (check_operator(current->str) == KO)
		current_is_word(current, before);
	if (before && check_operator(before->str) == OK)
		put_redir_type(current, before);
}

void	put_redir_type(t_token *current, t_token *before)
{
	if (before->type == IN_REDIR_TYPE)
		current->type = INFILE_TYPE;
	else if (before->type == OUT_REDIR_TYPE)
		current->type = OUTFILE_TYPE;
	else if (before->type == HERE_DOC_TYPE)
		current->type = HD_LIMITER_TYPE;
	else if (before->type == HD_APPEND_TYPE)
		current->type = APPEND_FILE_TYPE;
	else if (before->type == PIPE_TYPE)
	{
		if (current->type == WORD_TYPE)
			current->type = CMD_TYPE;
		set_builtin_type(current);
	}
	reset_operator_type(current);
}

void	current_is_word(t_token *current, t_token *before)
{
	current->type = WORD_TYPE;
	if (current->index == 0)
	{
		current->type = CMD_TYPE;
		set_builtin_type(current);
	}
	if (current->str[0] == '-')
	{
		current->type = OPT_TYPE;
		if (before && before->type == WORD_TYPE)
		{
			before->type = CMD_TYPE;
			if (is_builtin(before->str) == OK)
				before->type = BUILTIN_TYPE;
		}
	}
	else if (current->index > 0 && (before->type == OPT_TYPE
			|| before->type == CMD_TYPE || before->type == BUILTIN_TYPE
			|| before->type == ARG_TYPE))
		current->type = ARG_TYPE;
	else if (current->index > 0 && (ft_strncmp(before->str, "cd",
				ft_strlen(before->str)) == 0) && current->str[0] != '-')
		current->type = ARG_TYPE;
}
