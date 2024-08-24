
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

static int check_word(t_list *actual, t_list *before)
{
    t_token *content = actual->content;
    t_token *b_content = before ? before->content : NULL;

    if (!before || b_content->str[0] == '|' || b_content->type == CMD_TYPE)
    {
        content->type = CMD_TYPE;
        return (1);
    }
    content->type = ARG_TYPE;
    return (1);
}

static int is_valid_option(t_list *before)
{
    if (!before) return 0;

    t_token *b = before->content;

    if (check_operator(b->str) == OK)
	return 0;
    if (b->type == ARG_TYPE)
	return 1;
    return (b->str[0] == '-') ? 1 : 0;
}

static int is_valid_redirection(t_list *actual, t_list *before)
{
    if (!actual->next || !before) return 0;

    t_token *next = (t_token *)actual->next->content;
    t_token *b = before->content;

    if (check_operator(b->str) == OK) return 0;
    if (check_operator(next->str) == OK) return 0;

    return 1;
}

static void update_content_type(t_token *content, int type)
{
    content->type = type;
}

int check_lexical(t_list *token)
{
    t_list *actual = token;
    t_list *before = NULL;

    while (actual)
    {
        t_token *content = actual->content;

        if (check_operator(content->str) == OK)
        {
            if (!is_valid_redirection(actual, before))
                return (0);
        }
        else if (content->str[0] == '-')
        {
            if (!is_valid_option(before))
                return (0);
            update_content_type(content, OPT_TYPE);
        }
        else
        {
            if (!check_word(actual, before))
                return (0);
        }

        before = actual;
        actual = actual->next;
    }
    return (1);
}
