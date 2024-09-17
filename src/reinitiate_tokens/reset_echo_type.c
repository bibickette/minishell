/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_echo_type.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:00:54 by phwang            #+#    #+#             */
/*   Updated: 2024/09/14 18:08:28 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_token_flag_echo(t_list *tmp)
{
	if (((t_token *)tmp->content)->str[0] == '-')
	{
		if (ft_strcmp(((t_token *)tmp->content)->str, "-e") == 0
			|| ft_strcmp(((t_token *)tmp->content)->str, "-E") == 0)
			return (ft_putstr_fd(ECHO_ERR, STDERR_FILENO), KO);
		else if (is_echo_flag(((t_token *)tmp->content)->str) == OK)
			((t_token *)tmp->content)->type = OPT_TYPE;
		else
			((t_token *)tmp->content)->type = ARG_TYPE;
	}
	return (OK);
}

int	set_the_reset_echo(t_list *tmp)
{
	if (tmp->next == NULL)
		return (OK);
	tmp = tmp->next;
	if (set_token_flag_echo(tmp) == KO)
		return (KO);
	if (tmp->next == NULL)
		return (OK);
	tmp = tmp->next;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == PIPE_TYPE)
			return(OK);
		if (is_arg_for_echo(tmp) == OK)
			((t_token *)tmp->content)->type = ARG_TYPE;
		if (tmp->next == NULL)
			return (OK);
		tmp = tmp->next;
	}
	return (OK);
}

int	reset_arg_if_echo(t_list *head)
{
	t_list	*tmp;

	tmp = head;
	while (tmp)
	{
		if (is_cd(tmp) == OK)
			return (OK);
		if ((((t_token *)tmp->content)->type == BUILTIN_TYPE)
			&& ft_strcmp(((t_token *)tmp->content)->str, "echo") == 0)
			if (set_the_reset_echo(tmp) == KO)
				return (KO);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	return (OK);
}

int	is_echo_flag(char *str)
{
	int	i;

	i = 0;
	if (str[0] != '-' || str[1] != 'n')
		return (KO);
	while (str[++i])
	{
		if (str[i] != 'n')
			return (KO);
	}
	return (OK);
}
