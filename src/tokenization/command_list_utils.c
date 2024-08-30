/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexplor <hexplor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 13:30:12 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/30 15:34:41 by hexplor          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	increment_actual(t_list **actual, t_token **actual_content)
{
	*actual = (*actual)->next;
	if (*actual)
		*actual_content = (*actual)->content;
}

char	**add_option(char **options, char *new_option, int *size)
{
	char	**new_options;
	int		i;

	new_options = ft_calloc(*size + 2, sizeof(char *));
	if (!new_options)
		return (NULL);
	i = 0;
	while (i < *size)
	{
		new_options[i] = options[i];
		i++;
	}
	new_options[i] = ft_strdup(new_option);
	new_options[++i] = NULL;
	(*size)++;
	free(options);
	return (new_options);
}

char	**add_argument(char **args, char *new_arg, int *size)
{
	char	**new_args;
	int		i;

	new_args = ft_calloc(*size + 2, sizeof(char *));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i < *size)
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[i] = ft_strdup(new_arg);
	new_args[++i] = NULL;
	(*size)++;
	free(args);
	return (new_args);
}

void	process_command(t_list **actual, t_token **actual_content,
		t_command *content)
{
	if (check_operator((*actual_content)->str) == OK)
		return ;
	content->command = ft_strdup((*actual_content)->str);
	increment_actual(actual, actual_content);
}

void	process_options(t_list **actual, t_token **actual_content,
		t_command *content)
{
	int size;

	size = 0;
	while (*actual && (*actual_content)->str[0] == '-')
	{
		content->option = add_option(content->option, (*actual_content)->str,
				&size);
		increment_actual(actual, actual_content);
	}
}