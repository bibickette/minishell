/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:29:34 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/18 12:44:26 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_cmd(t_list *token, int fd_out)
{
	int		flag;
	t_list	*tmp;

	tmp = token;
	flag = 0;
	while (tmp)
	{
		if (is_echo_token(tmp, fd_out, &flag) == OK)
			break ;
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
	if (flag == 0)
		ft_putstr_fd("\n", fd_out);
}

int	is_echo_token(t_list *tmp, int fd_out, int *flag)
{
	if (((t_token *)tmp->content)->type == BUILTIN_TYPE
		&& ft_strncmp(((t_token *)tmp->content)->str, "echo",
			ft_strlen(((t_token *)tmp->content)->str)) == 0)
	{
		if (tmp->next == NULL)
			return (OK);
		tmp = tmp->next;
		if (((t_token *)tmp->content)->type == OPT_TYPE)
			*flag = 1;
		else
		{
			ft_putstr_fd(((t_token *)tmp->content)->str, fd_out);
			if (tmp->next == NULL
				|| ((t_token *)tmp->next->content)->type == PIPE_TYPE)
				return (OK);
			ft_putstr_fd(" ", fd_out);
		}
		print_echo_arg(tmp, fd_out);
		return (OK);
	}
	return (KO);
}

void	print_echo_arg(t_list *tmp, int fd_out)
{
	if (tmp->next == NULL)
		return ;
	tmp = tmp->next;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == ARG_TYPE)
		{
			ft_putstr_fd(((t_token *)tmp->content)->str, fd_out);
			if (tmp->next == NULL
				|| ((t_token *)tmp->next->content)->type == PIPE_TYPE)
				break ;
			ft_putstr_fd(" ", fd_out);
		}
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
	}
}
