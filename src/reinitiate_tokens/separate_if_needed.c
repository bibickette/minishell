/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_if_needed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:28:35 by phwang            #+#    #+#             */
/*   Updated: 2024/09/14 16:54:37 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	separate_if_needed(t_data *minishell, t_list *token)
{
	t_list	*tmp;
	t_list	*after;

	tmp = token;
	after = tmp->next;
	while (tmp)
	{
		if (((t_token *)tmp->content)->quote == N_QUOTE)
		{
			if (has_space(((t_token *)tmp->content)->str) == OK)
			{
				if (separate_token(tmp, after) == KO)
				{
					minishell->last_status = 2;
					return (KO);
				}
			}
		}
		if (after == NULL)
			break ;
		tmp = after;
		after = after->next;
	}
	return (OK);
}

int	separate_token(t_list *to_separate,
		t_list *after)
{
	char	**separated;
	t_list	*new_list;
	int		y;

	y = 0;
	new_list = NULL;
	separated = ft_split(((t_token *)to_separate->content)->str, ' ');
	if (!separated)
		return (ft_putstr_fd(SPLIT_ERR, STDERR_FILENO), KO);
	free(((t_token *)to_separate->content)->str);
	((t_token *)to_separate->content)->str = NULL;
	((t_token *)to_separate->content)->str = ft_strdup(separated[0]);
	if (!((t_token *)to_separate->content)->str)
	{
		free_double_char(&separated);
		return (ft_putstr_fd(STRDUP_ERR, STDERR_FILENO), KO);
	}
	while (separated[++y])
		add_token(&new_list, separated[y]);
	put_separate_list_in_token(new_list, to_separate);
	free_double_char(&separated);
	if (after)
		ft_lstlast(new_list)->next = after;
	return (OK);
}

void	put_separate_list_in_token(t_list *new_list, t_list *to_separate)
{
	t_list	*tmp;
	t_list	*other_tmp;

	tmp = new_list;
	other_tmp = to_separate;
	while (tmp)
	{
		other_tmp->next = tmp;
		((t_token *)tmp->content)->index = \
		((t_token *)to_separate->content)->index;
		((t_token *)tmp->content)->quote = \
		((t_token *)to_separate->content)->quote;
		if (tmp->next == NULL)
			break ;
		other_tmp = tmp;
		tmp = tmp->next;
	}
}

int	has_space(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == ' ')
			return (OK);
	return (KO);
}
