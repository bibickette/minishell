/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token_order.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 00:47:36 by phwang            #+#    #+#             */
/*   Updated: 2024/09/03 17:56:49 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_token_operator_order(t_list *token, t_data *minishell)
{
	t_list	*tmp;

	tmp = token;
	while (tmp)
	{
		if ((ft_strncmp(((t_token *)tmp->content)->str, "||", 2) == 0)
			|| (check_operator(((t_token *)tmp->content)->str) == OK
				&& tmp->next == NULL)
			|| (((t_token *)tmp->content)->str[0] == '|'
				&& ((t_token *)tmp->next->content)->str[0] == '|')
			|| (check_operator(((t_token *)tmp->content)->str) == OK
				&& check_operator(((t_token *)tmp->next->content)->str) == OK
				&& ((t_token *)tmp->content)->str[0] != '|')
			|| (((t_token *)tmp->content)->index == 0
				&& ((t_token *)tmp->content)->type == PIPE_TYPE))
		{
			minishell->last_status = 2;
			return (ft_putstr_fd(SYNTAX_ERR, STDERR_FILENO), KO);
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (OK);
}
/*

si je suis sur un operateur autre que |
ne pas accepter 2 op daffilé
si cest | alors celui dapres peut etre un op > <
mais aps avant

si je suis sur un builtin qui naccepte pas les opt ou arg, renvoyer erreur

*/