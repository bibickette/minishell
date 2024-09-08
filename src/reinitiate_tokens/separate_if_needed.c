/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_if_needed.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:28:35 by phwang            #+#    #+#             */
/*   Updated: 2024/09/08 17:20:17 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void separate_if_needed(t_data *minishell, t_list *token)
{
	t_list *tmp;
	t_list *before;
	before = NULL;
	tmp  = token;
	while(tmp)
	{
		if(((t_token *)tmp->content)->quote == N_QUOTE)
		{
			if(has_space(((t_token *)tmp->content)->str) == OK)
			{
				separate_token(&token, before, tmp, tmp->next);
			}
		}
		if(tmp->next == NULL)
			break;
		before = tmp;
		tmp = tmp->next;
	}
	// print_token(minishell->token);
}

int separate_token(t_list **token, t_list *before, t_list *to_separate, t_list *after)
{
	char **separated;
	int i = -1;
	t_list **new_list;
	t_list *new_element;
	
	new_list = NULL;
	new_element = NULL;
	separated = ft_split(((t_token *)to_separate->content)->str, ' ');
	if(!separated)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	while(separated[++i])
	{
		// new_element = ft_lstnew_custom(separated[i]);
		// ((t_token *)new_element->content)->index = ((t_token *)to_separate->content)->index;
		// if(!new_list)
		// 	return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
		ft_lstadd_back_libft(new_list, ft_lstnew_custom(separated[i]));
	}
	ft_lstiter(*new_list, print_token);
	if(!before && !after)
	{
		*token = *new_list;
	}
	if(before)
	{
		before->next = *new_list;
		printf("before: %s\n", ((t_token *)before->content)->str);
	}
	// printf("quote to separate: %s\n", ((t_token *)to_separate->content)->str);
	else if(after)
	{
		ft_lstlast(*new_list)->next = after;
		printf("next_one: %s\n", ((t_token *)after->content)->str);
	}
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