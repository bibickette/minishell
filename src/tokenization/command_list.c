/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:56:24 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/20 23:43:20 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	incremente_actual(t_list **actual, t_token **actual_content)
{
	*actual = (*actual)->next;
	if (*actual)
		*actual_content = (*actual)->content;
}

t_list	*command_listing(t_list *token, int *ret)
{
	t_list	*actual;
	t_list	*command_list;
	t_token *actual_content;
	t_command *content;
	int	action;
	int	i;

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
			ft_printf("je cherche une commande\n");
			ft_printf("commande trouvee: %s\n", actual_content->str);
			if (ft_strlen(actual_content->str) > 50)
			{
				ft_printf("grosse commande\n");
				*ret = 1;
				return (command_list);
			}
			ft_strlcpy(content->command, actual_content->str, 50); 
			incremente_actual(&actual, &actual_content);
			action = 1;
		}
		if (action == 1 && actual != NULL)
		{
			ft_printf("je cherche des options\n");
			i = -1;
			while (actual_content->str[0] == '-' && actual)
			{
				ft_printf("options trouvee: %s\n", actual_content->str);
				if (ft_strlen(actual_content->str) > 50 || i > 50)
				{
					ft_printf("grosse option\n");
					*ret = 1;
					return (command_list);
				}
				ft_strlcpy(content->option[++i], actual_content->str, 50);
				incremente_actual(&actual, &actual_content);
			}
			action = 2;
		}
		if (action == 2 && actual != NULL)
		{
			ft_printf("je cherche des arguments\n");
			i = -1;
			while (check_operator(actual_content->str) == KO && actual)
			{
				ft_printf("argument trouvee: %s\n", actual_content->str);
				if (ft_strlen(actual_content->str) > 50 || i > 50)
				{
					ft_printf("gros arg\n");
					*ret = 1;
					return (command_list);
				}
				ft_strlcpy(content->arg[++i], actual_content->str, 50);
				incremente_actual(&actual, &actual_content);
			}
			action = 3;
		}
		if (action == 3 && actual != NULL)
		{
			ft_printf("je cherche des redirections\n");
			if (actual_content->str[0] == '>' || actual_content->str[0] == '<')
			{
				printf("redirection trouvee: %s\n", actual_content->str);
				content->redirection[0] = actual_content->str[0];
				incremente_actual(&actual, &actual_content);
				ft_strlcpy(content->output, actual_content->str, 50);
				ft_printf("output: %s\n", content->output);
			}
			else if (actual_content->str[0] == '|')
			{
				printf("redirection trouvee: %s\n", actual_content->str);
				content->pipe = 1;
			}
			action = 0;
		}
		ft_printf("je push la commande\n");
		if (command_list == NULL)
			command_list = ft_lstnew_libft(&content);
		else
			ft_lstadd_back_libft(&command_list, ft_lstnew_libft(&content));
		if (actual)
			incremente_actual(&actual, &actual_content);
		if (ret)
			break ;
	}
	ret = 0;
	return (command_list);
}
