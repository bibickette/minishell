/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apocalypse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 00:15:48 by phwang            #+#    #+#             */
/*   Updated: 2024/08/12 01:17:27 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apocalypse(t_data *minishell)
{
	get_next_line(STDIN_FILENO, 1);
	free_builtins(minishell->builtins);
	free_lists(minishell);
	if (minishell->path)
		free_double_char(minishell->path);
	minishell->path = 0;
	if (minishell->here_doc == OK)
		unlink(HERE_DOC);
	if (minishell)
		free(minishell);
	minishell = 0;
	return ;
}

void	free_builtins(t_builtin *builtins)
{
	if (builtins->env)
		free_double_char(builtins->env);
	builtins->env = 0;
	if (builtins->pwd)
		free(builtins->pwd);
	builtins->pwd = 0;
	if (builtins->export)
		ft_lstclear_custom_bis(builtins->export);
	builtins->export = 0;
	if (builtins)
		free(builtins);
	builtins = 0;
}

void	free_lists(t_data *minishell)
{
	if (minishell->token)
		free(minishell->token);
	minishell->token = 0;
	if (minishell->history)
		clear__history(&minishell);
	minishell->history = 0;
}

void	ft_lstclear_custom_bis(t_list *head)
{
	t_list	*tmp;

	while (head)
	{
		tmp = head->next;
		free(head);
		head = 0;
		head = tmp;
	}
}
