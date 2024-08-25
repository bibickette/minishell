/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:56:24 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/24 17:11:44 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell.h"

static void	incremente_actual(t_list **actual, t_token **actual_content)
{
	*actual = (*actual)->next;
	if (*actual)
		*actual_content = (*actual)->content;
}

t_list	*command_listing(t_list *token)
{
	t_list *actual;
	t_list *command_list;
	t_token *actual_content;
	t_command *content;
	int action;
	int i;

	action = 0;
	if (!token)
		return (NULL);
	actual = token;
	actual_content = actual->content;
	command_list = NULL;
	while (actual)
	{
		content = calloc(1, sizeof(t_command));
		if (action == 0)
		{
			content->command = ft_strdup(actual_content->str);
			incremente_actual(&actual, &actual_content);
			action = 1;
		}
		if (action == 1 && actual != NULL)
		{
			i = 0;
			while (actual_content->str[0] == '-' && actual)
			{
				content->option = realloc(content->option, sizeof(char *) * (i + 2));
				content->option[i] = ft_strdup(actual_content->str);
				content->option[++i] = NULL;
				incremente_actual(&actual, &actual_content);
			}
			action = 2;
		}
		if (action == 2 && actual != NULL)
		{
			i = 0;
			while (check_operator(actual_content->str) == KO && actual)
			{
				content->arg = realloc(content->arg, sizeof(char *) * (i + 2));
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
