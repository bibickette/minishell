/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:08:07 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/18 14:38:04 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exit(t_data *minishell, char *prompt)
{
	int	last_status;

	last_status = minishell->last_status;
	if (prompt)
		free(prompt);
	apocalypse(minishell);
	exit(last_status);
}

void	first_token_is_exit(char *prompt, t_data *minishell, t_list *token)
{
	if (!token)
		return ;
	if (ft_strcmp(((t_token *)token->content)->str, "exit") == 0)
	{
		if (is_return_value(token->next) == KO)
		{
			minishell->last_status = 2;
			ft_putstr_fd(EXIT_ERR, STDERR_FILENO);
		}
		else if (token->next)
			minishell->last_status = \
			set_exit_arg(ft_atoi(((t_token *)token->next->content)->str));
		ft_lstclear_custom(&token, free);
		ft_lstclear_custom(&minishell->brut_list, free);
		handle_exit(minishell, prompt);
	}
}

int	is_return_value(t_list *node)
{
	int	i;

	if (!node)
		return (OK);
	i = -1;
	if ((((t_token *)node->content)->str[0] == '+'
			|| ((t_token *)node->content)->str[0] == '-')
		&& ((t_token *)node->content)->str[1] == '\0')
		return (KO);
	else if ((((t_token *)node->content)->str[0] == '+'
			|| ((t_token *)node->content)->str[0] == '-'))
		i++;
	while (((t_token *)node->content)->str[++i])
		if (ft_isdigit(((t_token *)node->content)->str[i]) == 0)
			return (KO);
	return (OK);
}

int	set_exit_arg(long int status)
{
	if (status > 255 || status < 0)
		status = status % 256;
	return (status);
}
