/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:20:13 by phwang            #+#    #+#             */
/*   Updated: 2024/09/01 22:31:26 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_token(t_list *token, t_list *is_next_token)
{
	t_list	*tmp_head;
	t_list	*next_tmp;

	tmp_head = token;
	while (tmp_head)
	{
		if (tmp_head->next == is_next_token)
		{
			((t_token *)tmp_head->content)->str = \
			strjoin_wfree(((t_token *)tmp_head->content)->str,
					((t_token *)is_next_token->content)->str);
			if (!((t_token *)tmp_head->content)->str)
				return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
			stick_next_token(is_next_token, &tmp_head, &next_tmp);
		}
		if (tmp_head->next == NULL)
			break ;
		tmp_head = tmp_head->next;
	}
	return (OK);
}

void	stick_next_token(t_list *is_next_token, t_list **tmp_head,
		t_list **next_tmp)
{
	if (is_next_token->next == NULL)
	{
		free(((t_token *)is_next_token->content)->str);
		free(is_next_token->content);
		free(is_next_token);
		(*tmp_head)->next = NULL;
	}
	else
	{
		(*next_tmp) = is_next_token->next;
		(*tmp_head)->next = (*next_tmp);
		free(((t_token *)is_next_token->content)->str);
		free(is_next_token->content);
		free(is_next_token);
	}
}
