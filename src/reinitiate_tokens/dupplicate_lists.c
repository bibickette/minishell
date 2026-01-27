/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupplicate_lists.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <phwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 18:24:30 by phwang            #+#    #+#             */
/*   Updated: 2026/01/27 18:16:29 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dupplicate_list(t_list *token, t_list **brut_list)
{
	t_list	*tmp_head;
	int		index;

	tmp_head = token;
	while (tmp_head)
	{
		ft_lstadd_back(brut_list,
			ft_lstnew_custom(((t_token *)tmp_head->content)->str));
		if (tmp_head->next == NULL)
			break ;
		tmp_head = tmp_head->next;
	}
	tmp_head = *brut_list;
	index = 0;
	while (tmp_head)
	{
		((t_token *)tmp_head->content)->index = index++;
		if (tmp_head->next == NULL)
			break ;
		tmp_head = tmp_head->next;
	}
	set_quote_n_put_back(token, *brut_list);
	return (OK);
}

int	set_quote_n_put_back(t_list *token, t_list *brut_list)
{
	t_list	*tmp_head;
	t_list	*tmp_brut;

	tmp_head = token;
	tmp_brut = brut_list;
	while (tmp_head)
	{
		((t_token *)tmp_brut->content)->quote = \
		((t_token *)tmp_head->content)->quote;
		if (((t_token *)tmp_brut->content)->quote != N_QUOTE)
		{
			if (((t_token *)tmp_brut->content)->quote == S_QUOTE)
				put_quote_back(&((t_token *)tmp_brut->content)->str, 39);
			else if (((t_token *)tmp_brut->content)->quote == D_QUOTE)
				put_quote_back(&((t_token *)tmp_brut->content)->str, 34);
		}
		if (tmp_head->next == NULL)
			break ;
		tmp_head = tmp_head->next;
		tmp_brut = tmp_brut->next;
	}
	return (OK);
}

int	put_quote_back(char **str, char quote)
{
	int		len;
	char	*with_quote;

	len = ft_strlen(*str);
	with_quote = ft_calloc(sizeof(char), (len + 3));
	if (!with_quote)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	with_quote[0] = quote;
	len = -1;
	while ((*str)[++len])
		with_quote[len + 1] = (*str)[len];
	with_quote[len + 1] = quote;
	with_quote[len + 2] = '\0';
	free(*str);
	*str = 0;
	*str = with_quote;
	return (OK);
}

void	set_index_again(t_list *token, t_list *brut_list)
{
	t_list	*tmp;
	int		index;

	tmp = token;
	index = 0;
	while (tmp)
	{
		((t_token *)tmp->content)->index = index;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
		index++;
	}
	tmp = brut_list;
	index = 0;
	while (tmp)
	{
		((t_token *)tmp->content)->index = index++;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}
