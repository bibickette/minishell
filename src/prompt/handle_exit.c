/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 15:08:07 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/13 01:30:04 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_exit(t_data *minishell, char *prompt)
{
	if (prompt)
		free(prompt);
	apocalypse(minishell);
	exit(0);
}

void	first_token_is_exit(char *prompt, t_data *minishell, t_list *token)
{
	if (!token)
		return ;
	if (ft_strcmp(((t_token *)token->content)->str, "exit") == 0)
	{
		ft_lstclear_custom(&token, free);
		ft_lstclear_custom(&minishell->brut_list, free);
		handle_exit(minishell, prompt);
	}
}
