/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:00:16 by phwang            #+#    #+#             */
/*   Updated: 2024/09/02 02:11:05 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lf_spechar_list(t_list *token)
{
	t_list	*tmp;

	tmp = token;
	while (tmp)
	{
		if (((t_token *)tmp->content)->quote == N_QUOTE)
			if (check_special_char(((t_token *)tmp->content)->str) == KO)
				return (KO);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (OK);
}
/*
cherche les caractères spéciaux dans la liste de tokens sur les tokens unquoted
*/

int	check_special_char(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] == '~' || prompt[i] == '&' || prompt[i] == '`'
			|| prompt[i] == '[' || prompt[i] == ']' || prompt[i] == '{'
			|| prompt[i] == '}' || prompt[i] == '*' || prompt[i] == ';'
			|| prompt[i] == ':' || prompt[i] == '\\' || prompt[i] == '('
			|| prompt[i] == ')' || prompt[i] == '?' || prompt[i] == '@'
			|| prompt[i] == '#' || prompt[i] == '%' || prompt[i] == '^')
			return (ft_putstr_fd(SPECIAL_CHAR_ERR, STDERR_FILENO), KO);
	}
	return (OK);
}
