/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_tokens_if_needed.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:25:24 by phwang            #+#    #+#             */
/*   Updated: 2024/09/03 21:30:52 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start_join_token_if_needed(t_list *token, char *prompt, t_list *brut_list)
{
	char	*tmp_prompt;

	tmp_prompt = prompt;
	if (join_token_if_needed(token, prompt, brut_list, &tmp_prompt) == KO)
		return (KO);
	return (OK);
}

int	join_token_if_needed(t_list *token, char *prompt, t_list *brut_list,
		char **t_pt)
{
	t_list		*t_b;
	t_list		*tmp_token;
	static char	*n_p = NULL;

	tmp_token = token;
	t_b = brut_list;
	while (t_b)
	{
		if (load_new_prompt(&n_p, t_pt, ((t_token *)t_b->content)->str) == KO)
			return (KO);
		if (check_new_prompt(n_p, ((t_token *)t_b->content)->str) == OK)
		{
			if (increment_lists(&tmp_token, &t_b) == KO)
				break ;
		}
		else if (line_economy(n_p, ((t_token *)t_b->content)->str) == OK)
		{
			if (join_token_in_lists(token, brut_list, &tmp_token, &t_b) == KO)
				return (KO);
			*t_pt = prompt;
		}
		else if (increment_lists(&tmp_token, &t_b) == KO)
			break ;
	}
	return (OK);
}

int	load_new_prompt(char **new_prompt, char **tmp_prompt, char *token_str)
{
	*new_prompt = ft_strnstr(*tmp_prompt, token_str, ft_strlen(*tmp_prompt));
	if (!*new_prompt)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	*tmp_prompt = *new_prompt;
	return (OK);
}

int	join_token_in_lists(t_list *token, t_list *brut_list, t_list **tmp_token,
		t_list **tmp_brut)
{
	t_list	*is_next_token;

	is_next_token = (*tmp_brut)->next;
	if (join_token(brut_list, is_next_token) == KO)
		return (KO);
	is_next_token = (*tmp_token)->next;
	if (join_token(token, is_next_token))
		return (KO);
	*tmp_brut = brut_list;
	*tmp_token = token;
	return (OK);
}

int	increment_lists(t_list **token, t_list **brut_list)
{
	if ((*brut_list)->next == NULL)
		return (KO);
	*brut_list = (*brut_list)->next;
	*token = (*token)->next;
	return (OK);
}
