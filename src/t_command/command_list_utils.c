/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 16:11:13 by phwang            #+#    #+#             */
/*   Updated: 2024/09/08 17:34:08 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_arguments_and_options(t_list **actual, t_token **actual_content, t_command *content)
{
	int	arg_size = 0;
	int	opt_size = 0;

	while (*actual)
	{
		if ((*actual_content)->type == ARG_TYPE)
			content->arg = add_argument(content->arg, (*actual_content)->str, &arg_size);
		else if ((*actual_content)->type == OPT_TYPE)
			content->option = add_option(content->option, (*actual_content)->str, &opt_size);
		else
			break;
		increment_actual(actual, actual_content);
	}
}

void	increment_actual(t_list **actual, t_token **actual_content)
{
	if (*actual)
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

void	process_command(t_list **actual, t_token **actual_content, t_command *content)
{
	if ((*actual_content)->type != CMD_TYPE && (*actual_content)->type != BUILTIN_TYPE)
		return ;
	content->command = ft_strdup((*actual_content)->str);
}
