/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 21:20:13 by phwang            #+#    #+#             */
/*   Updated: 2024/09/14 16:54:26 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	join_token(t_list *token, int token_nb)
{
	t_list	*tmp_head;
	t_list	*next_tmp;
	int		index;

	tmp_head = token;
	index = 0;
	while (tmp_head)
	{
		if (tmp_head->next
			&& ((t_token *)tmp_head->next->content)->index == token_nb)
		{
			((t_token *)tmp_head->content)->str = \
			strjoin_wfree(((t_token *)tmp_head->content)->str,
					((t_token *)tmp_head->next->content)->str);
			if (!((t_token *)tmp_head->content)->str)
				return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
			stick_next_token(tmp_head->next, &tmp_head, &next_tmp);
		}
		if (tmp_head->next == NULL)
			break ;
		tmp_head = tmp_head->next;
		index++;
	}
	return (OK);
}

void	stick_next_token(t_list *is_next_token, t_list **tmp_head,
		t_list **next_tmp)
{
	if (is_next_token->next == NULL)
	{
		free(((t_token *)is_next_token->content)->str);
		((t_token *)is_next_token->content)->str = NULL;
		free(is_next_token->content);
		is_next_token->content = 0;
		free(is_next_token);
		is_next_token = 0;
		(*tmp_head)->next = NULL;
	}
	else
	{
		(*next_tmp) = is_next_token->next;
		(*tmp_head)->next = (*next_tmp);
		free(((t_token *)is_next_token->content)->str);
		((t_token *)is_next_token->content)->str = NULL;
		free(is_next_token->content);
		is_next_token->content = 0;
		free(is_next_token);
		is_next_token = 0;
	}
}
