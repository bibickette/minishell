/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexplor <hexplor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:56:24 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/30 15:41:55 by hexplor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_arguments(t_list **actual, t_token **actual_content,
		t_command *content)
{
	int	size;

	size = 0;
	while (*actual && check_operator((*actual_content)->str) == KO)
	{
		content->arg = add_argument(content->arg, (*actual_content)->str,
				&size);
		increment_actual(actual, actual_content);
	}
}

static void	process_redirection_and_pipe(t_list **actual,
		t_token **actual_content, t_command *content)
{
	if ((*actual_content)->str[0] == '>')
	{
		content->redirection = ft_strdup((*actual_content)->str);
		increment_actual(actual, actual_content);
		if (*actual)
			content->output = ft_strdup((*actual_content)->str);
	}
	else if ((*actual_content)->str[0] == '<')
	{
		content->redirection = ft_strdup((*actual_content)->str);
		increment_actual(actual, actual_content);
		if (*actual)
			content->input = ft_strdup((*actual_content)->str);
	}
	if ((*actual_content)->str[0] == '|')
		content->pipe = 1;
}

t_list	*command_listing(t_list *token)
{
	t_list		*actual;
	t_list		*command_list;
	t_token		*actual_content;
	t_command	*content;

	if (!token)
		return (NULL);
	actual = token;
	command_list = NULL;
	actual_content = actual->content;
	while (actual)
	{
		content = ft_calloc(1, sizeof(t_command));
		if (!content)
			return (NULL);
		process_command(&actual, &actual_content, content);
		if (actual)
			process_options(&actual, &actual_content, content);
		if (actual)
			process_arguments(&actual, &actual_content, content);
		if (actual)
			process_redirection_and_pipe(&actual, &actual_content, content);
		if (!command_list)
			command_list = ft_lstnew_libft(content);
		else
			ft_lstadd_back_libft(&command_list, ft_lstnew_libft(content));
		if (actual)
			increment_actual(&actual, &actual_content);
	}
	return (command_list);
}
