/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_token_type.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:01:03 by phwang            #+#    #+#             */
/*   Updated: 2024/09/03 18:23:46 by phwang           ###   ########.fr       */
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
		if (is_builtin(current->str) == OK)
		{
			current->type = BUILTIN_TYPE;
			if (ft_strncmp(current->str, "echo", ft_strlen(current->str)) == 0)
				current->builtin_type = BUILT_W_OPT;
			if (ft_strncmp(current->str, "env", ft_strlen(current->str)) == 0)
				current->builtin_type = BUILT_NO_OPT_ARG;
			else
				current->builtin_type = BUILT_NO_OPT_ARG;
		}
	}
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

void	current_is_word(t_token *current, t_token *before)
{
	current->type = WORD_TYPE;
	if (current->index == 0)
	{
		current->type = CMD_TYPE;
		if (is_builtin(current->str) == OK)
		{
			current->type = BUILTIN_TYPE;
			if (ft_strncmp(current->str, "echo", ft_strlen(current->str)) == 0)
				current->builtin_type = BUILT_W_OPT;
			if (ft_strncmp(current->str, "env", ft_strlen(current->str)) == 0)
				current->builtin_type = BUILT_NO_OPT_ARG;
			else
				current->builtin_type = BUILT_NO_OPT_ARG;
		}
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
	else if (current->str[0] == '$')
		current->type = DOLLAR_TYPE;
	else if (current->str[0] == '.')
		current->type = EXECUTABLE_TYPE;
	else if (current->index > 0 && (before->type == OPT_TYPE
			|| before->type == CMD_TYPE || before->type == BUILTIN_TYPE))
		current->type = ARG_TYPE;
	else if (current->index > 0 && before->type == ARG_TYPE)
		current->type = ARG_TYPE;
}
