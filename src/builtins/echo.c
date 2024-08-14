/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 12:29:34 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/14 17:47:33 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo_cmd(t_list *token, int fd_dest)
{
	t_list	*current;
	t_token	*current_token;
	int	n_flag;

	n_flag = 0;
	current = token;
	while (current && ft_strcmp(((t_token *)current->content)->str, "echo") != 0)
	{
		current = current->next;
		if (!current)
			return (KO);
	}
	current = current->next;
	if (current && ft_strcmp(((t_token *)current->content)->str, "-n") == 0)
	{
		n_flag = 1;
		current = current->next;
	}
	while (current && check_operator(((t_token *)current->content)->str) == KO)
	{
		current_token = (t_token *)current->content;
		ft_putstr_fd(current_token->str, fd_dest);
		current = current->next;
		if (current && check_operator(((t_token *)current->content)->str) == KO)
			ft_putstr_fd(" ", fd_dest);
	}
	if (n_flag == 0)
		ft_putstr_fd("\n", fd_dest);
	return (OK);
}
