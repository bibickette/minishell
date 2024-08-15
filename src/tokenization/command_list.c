/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:56:24 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/14 20:08:44 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_number_of_commands(t_list *token)
{
	t_list	*actual;
	t_token	*content;
	int		i;
	int		bit;

	bit = 0;
	i = 0;
	actual = (t_list *)token;
	content = (t_token *)actual->content;
	while (actual)
	{
		if (bit == 0) 
		{
			printf("command: %s\n", content->str);
			i++;
			bit = 1;
			if (actual->next != NULL)
			{
				actual = actual->next;
				content = (t_token *)actual->content;
			}
			else
				break;
		}
		if (check_operator(content->str) == OK)
			bit = 0;
		if (actual->next != NULL)
		{
			actual = actual->next;
			content = (t_token *)actual->content;
		}
		else
			break;
	}
	printf("nb_commands = %d\n", i);
	return (i);
}

static void	cpy_command(char *command, char *str)
{
	ft_strlcpy(command, str, ft_strlen(str) + 1);
}

void	command_listing(t_list *token, t_data *data)
{
	t_list	*actual;
	t_token	*content;
	char	**command;
	int		i;
	int		nb_commands;

	i = 0;
	command = NULL;
	nb_commands = count_number_of_commands(token);
	command = malloc((nb_commands + 1) * sizeof(char *));
	command[nb_commands] = NULL;
	actual = (t_list *)token;
	content = (t_token *)actual->content;
	while (actual && i < nb_commands && command[i])
	{
		if (check_operator(content->str) == KO && content->str[0] != '-')
		{
			command[i] = ft_calloc(ft_strlen(content->str) + 1, sizeof(char));
			cpy_command(command[i], content->str);
			i++;
		}
		actual = actual->next;
		content = (t_token *)actual->content;
	}
	data->command = command;
}
