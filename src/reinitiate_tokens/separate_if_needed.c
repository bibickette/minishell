/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_if_needed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:28:35 by phwang            #+#    #+#             */
/*   Updated: 2024/09/10 17:13:14 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void separate_if_needed(t_data *minishell, t_list *token)
{
	t_list *tmp;
	t_list *before;
	t_list *after;
	before = NULL;
	tmp  = token;
	after = tmp->next;
	while(tmp)
	{
		if(((t_token *)tmp->content)->quote == N_QUOTE)
		{
			if(has_space(((t_token *)tmp->content)->str) == OK)
			{
				separate_token(&token, before, tmp, after);
			}
		}
		if(after == NULL)
			break;
		before = tmp;
		tmp = after;
		after = after->next;
	}
	// print_token(minishell->token);
}

int separate_token(t_list **token, t_list *before, t_list *to_separate, t_list *after)
{
	char **separated;
	t_list *new_list;
	t_list *new_element;
	int y;
	
	y = 0;
	new_list = NULL;
	new_element = NULL;
	separated = ft_split(((t_token *)to_separate->content)->str, ' ');
	if(!separated)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	free(((t_token *)to_separate->content)->str);
	((t_token *)to_separate->content)->str = ft_strdup(separated[0]);
	while (separated[++y])
		add_token(&new_list, separated[y]);
	y = 0;
	t_list *tmp;
	tmp = new_list;
	t_list *other_tmp;
	other_tmp = to_separate;
	while(tmp)
	{
		other_tmp->next = tmp;
		((t_token *)tmp->content)->index = ((t_token *)to_separate->content)->index;
		((t_token *)tmp->content)->quote = ((t_token *)to_separate->content)->quote;
		if(tmp->next == NULL)
			break;
		other_tmp = tmp;
		tmp = tmp->next;
	}
	free_double_char(separated);
	if(after)
		ft_lstlast(new_list)->next = after;
	return (OK);
}

int has_space(char *str)
{
	int i;
	i = -1;
	while(str[++i])
		if(str[i] == ' ')
			return (OK);
	return (KO);
}
