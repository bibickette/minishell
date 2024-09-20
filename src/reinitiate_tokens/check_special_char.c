/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_special_char.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:00:16 by phwang            #+#    #+#             */
/*   Updated: 2024/09/20 19:45:01 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lf_spechar_list(t_data *minishell, t_list *token)
{
	t_list	*tmp;
	int		is_echo;

	is_echo = KO;
	tmp = token;
	while (tmp)
	{
		if (lf_n_quote(tmp, &is_echo) == KO)
		{
			minishell->last_status = 2;
			return (KO);
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (OK);
}
/*
cherche les caractères spéciaux dans la liste de tokens sur les tokens unquoted
*/

int	lf_n_quote(t_list *tmp, int *is_echo)
{
	if (((t_token *)tmp->content)->quote == N_QUOTE)
	{
		if (((t_token *)tmp->content)->type == PIPE_TYPE)
			(*is_echo) = KO;
		if ((((t_token *)tmp->content)->type == BUILTIN_TYPE)
			&& ft_strcmp(((t_token *)tmp->content)->str, "echo") == 0)
			(*is_echo) = OK;
		if ((*is_echo) == KO
			&& check_special_char(((t_token *)tmp->content)->str) == KO)
			return (KO);
	}
	return (OK);
}

int	check_special_char(char *prompt)
{
	int	i;

	i = -1;
	while (prompt[++i])
	{
		if (prompt[i] == '~' || prompt[i] == '*' || prompt[i] == ';'
			|| prompt[i] == '?' || prompt[i] == '&' || prompt[i] == '`'
			|| prompt[i] == '(' || prompt[i] == ')' || prompt[i] == '#'
			|| prompt[i] == '[' || prompt[i] == ']' || prompt[i] == '{'
			|| prompt[i] == '}' || prompt[i] == ':' || prompt[i] == '\\')
			return (ft_putstr_fd(SPECIAL_CHAR_ERR, STDERR_FILENO), KO);
	}
	return (OK);
}

int	check_more_special_char(char c)
{
	if (c == ' ' || c == '+' || c == '-' || c == '?' || c == 34 || c == 39
		|| c == '!' || c == '@' || c == '#' || c == '%' || c == '^')
		return (KO);
	else if (c == '<' || c == '>' || c == '~' || c == '/' || c == '`'
		|| c == '|' || c == '$' || c == '\t')
		return (KO);
	else if (c == '&' || c == '*' || c == '(' || c == ')' || c == '{'
		|| c == '}')
		return (KO);
	else if (c == '[' || c == ']' || c == '\\' || c == '.' || c == ','
		|| c == ';' || c == ':')
		return (KO);
	return (OK);
}
