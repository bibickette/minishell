/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:25:24 by phwang            #+#    #+#             */
/*   Updated: 2024/08/30 18:37:33 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	join_token_if_needed(t_list *token, char *prompt, t_list *brut_list)
{
	t_list	*tmp_head;
	t_list	*tmp_token;
	t_list	*is_next_token;
	char	*new_prompt;
	char	*tmp_prompt;

	tmp_token = token;
	tmp_head = brut_list;
	new_prompt = NULL;
	tmp_prompt = prompt;
	while (tmp_head)
	{
		new_prompt = ft_strnstr(tmp_prompt, ((t_token *)tmp_head->content)->str,
				ft_strlen(tmp_prompt));
		tmp_prompt = new_prompt;
		if (new_prompt[0] == '|' || new_prompt[0] == '<'
			|| new_prompt[0] == '>')
		{
			if (tmp_head->next == NULL)
				break ;
			tmp_head = tmp_head->next;
			tmp_token = tmp_token->next;
		}
		else if (new_prompt[ft_strlen(((t_token *)tmp_head->content)->str)] == '|'
			|| new_prompt[ft_strlen(((t_token *)tmp_head->content)->str)] == '>'
			|| new_prompt[ft_strlen(((t_token *)tmp_head->content)->str)] == '<')
		{
			if (tmp_head->next == NULL)
				break ;
			tmp_head = tmp_head->next;
			tmp_token = tmp_token->next;
		}
		else if (new_prompt[ft_strlen(((t_token *)tmp_head->content)->str)] != ' '
			&& new_prompt[ft_strlen(((t_token *)tmp_head->content)->str)] != '\0')
		{
			if (tmp_head->next)
			{
				is_next_token = tmp_head->next;
				join_token(brut_list, is_next_token);
				is_next_token = tmp_token->next;
				join_token(token, is_next_token);
				tmp_head = brut_list;
				tmp_token = token;
				tmp_prompt = prompt;
			}
		}
		else
		{
			if (tmp_head->next == NULL)
				break ;
			tmp_head = tmp_head->next;
			tmp_token = tmp_token->next;
		}
	}
}

void	join_token(t_list *token, t_list *is_next_token)
{
	t_list	*tmp_head;
	t_list	*next_tmp;

	tmp_head = token;
	while (tmp_head)
	{
		if (tmp_head->next == is_next_token)
		{
			((t_token *)tmp_head->content)->str = strjoin_wfree(((t_token *)tmp_head->content)->str,
					((t_token *)is_next_token->content)->str);
			if (is_next_token->next == NULL)
			{
				free(((t_token *)is_next_token->content)->str);
				free(is_next_token->content);
				free(is_next_token);
				tmp_head->next = NULL;
			}
			else
			{
				next_tmp = is_next_token->next;
				tmp_head->next = next_tmp;
				free(((t_token *)is_next_token->content)->str);
				free(is_next_token->content);
				free(is_next_token);
			}
		}
		if (tmp_head->next == NULL)
			break ;
		tmp_head = tmp_head->next;
	}
}
