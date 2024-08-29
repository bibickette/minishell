/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suppr_element.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 17:19:24 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/29 17:28:28 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*suppr_element(t_list **element)
{
	t_list	*tmp;
	t_token *token;
	t_list	*next;

	if (!element || !*element)
		return ;
	tmp = *element;
	if (tmp->next)
		next = tmp->next;
	else
		next = NULL;
	token = tmp->content;
	free(token->str);
	free(token);
	free(tmp);
	return (next);
}
