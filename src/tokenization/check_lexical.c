/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lexical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 13:55:13 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/23 13:26:07 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_word(t_list *actual, t_list *before)
{
	t_token *content;
	t_token *b_content;

	content = actual->content;
	if (before != NULL)
		b_content = before->content;
	if (before == NULL || b_content->str[0] == '|')
	{
		content->type = CMD_TYPE;
		return (1);
	}
	else
		content->type = ARG_TYPE;
	return (1);
}

static int	check_option(t_list *before)
{
	t_token	*b;

	if (before == NULL)
		return (0);
	b = before->content;
	if (check_operator(b->str) == OK)
		return (0);
	else if (b->type == ARG_TYPE)
		return (0);
	else if (b->str[0] == '-')
		return (1);
	return (1);
}

static int	check_redirection(t_list *actual, t_list *before)
{
	t_token *next;
	t_token *b;

	if (actual->next == NULL || before == NULL)
		return (0);
	next = (t_token *)actual->next->content;
	b = before->content;
	if (check_operator(b->str) == OK)
		return (0);
	else if (check_operator(next->str) == OK)
		return (0);
	return (1);
}

int	check_lexical(t_list *token)
{
	t_list	*actual;
	t_list	*before;
	t_token *content;

	actual = token;
	content = actual->content;
	before = NULL;
	while (actual)
	{
		if (content->str[0] == '-')
		{
			if (check_option(before) == 0)
				return (0);
		}
		else if (check_operator(content->str) == 1)
		{
			if (check_redirection(actual, before) == 0)
				return (0);
		}
		else
			check_word(actual, before);
		before = actual;
		actual = actual->next;
		if (actual)
			content = actual->content;
	}
	return (1);
}
