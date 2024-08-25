/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:56:24 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/25 15:48:36 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	incremente_actual(t_list **actual, t_token **actual_content)
{
	*actual = (*actual)->next;
	if (*actual)
		*actual_content = (*actual)->content;
}

t_list	*command_listing(t_list *token)
{
	int			i;
	int			action;
	t_list		*actual;
	t_list		*command_list;
	t_token		*actual_content;
	t_command	*content;

	action = 0;
	if (!token)
		return (NULL);
	actual = token;
	actual_content = actual->content;
	command_list = NULL;
	while (actual)
	{
		content = ft_calloc(1, sizeof(t_command));
		if (action == 0)
		{
			content->command = ft_strdup(actual_content->str);
			incremente_actual(&actual, &actual_content);
			action = 1;
		}
		if (action == 1 && actual != NULL)
		{
			i = 0;
			content->option = ft_calloc(2, sizeof(char *));
			content->option[i] = ft_strdup(actual_content->str);
			content->option[++i] = NULL;
			incremente_actual(&actual, &actual_content);
			while (actual_content->str[0] == '-' && actual)
			{
				if (content->option == NULL || !content->option[0])
					content->option = ft_calloc(2, sizeof(char *));
				else
					content->option = ft_realloc(content->option, sizeof(char *) * (i + 2));
				content->option[i] = ft_strdup(actual_content->str);
				content->option[++i] = NULL;
				incremente_actual(&actual, &actual_content);
			}
			action = 2;
		}
		if (action == 2 && actual != NULL)
		{
			i = 0;
			content->arg = ft_calloc(2, sizeof(char *));
			content->arg[i] = ft_strdup(actual_content->str);
			content->arg[++i] = NULL;
			incremente_actual(&actual, &actual_content);
			while (check_operator(actual_content->str) == KO && actual)
			{
				content->arg = ft_realloc(content->arg, sizeof(char *) * (i + 2));
				content->arg[i] = ft_strdup(actual_content->str);
				content->arg[++i] = NULL;
				incremente_actual(&actual, &actual_content);
			}
			action = 3;
		}
		if (action == 3 && actual != NULL)
		{
			if (actual_content->str[0] == '>' || actual_content->str[0] == '<')
			{
				content->redirection = ft_strdup(actual_content->str);
				incremente_actual(&actual, &actual_content);
				content->output = ft_strdup(actual_content->str);
			}
			if (actual_content->str[0] == '|')
				content->pipe = 1;
			action = 0;
		}
		if (command_list == NULL)
			command_list = ft_lstnew_libft(content);
		else
			ft_lstadd_back_libft(&command_list, ft_lstnew_libft(content));
		if (actual)
			incremente_actual(&actual, &actual_content);
	}
	return (command_list);
}
