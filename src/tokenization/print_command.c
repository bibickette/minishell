/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:29:48 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/25 14:42:14 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_double_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		printf("\t");
		while (tab[i])
		{
			printf(" %s", tab[i]);
			i++;
		}
		printf("\n");
	}
}

static void	h_pipe(t_command *command)
{
	if (command->pipe)
		printf("pipe: yes\n");
	else
		printf("pipe: no\n");
}

void	print_command(void *content)
{
	t_command	*command;

	if (!content)
		return ;
	command = (t_command *)content;
	if (command->command)
		printf("command:\t%s\n", command->command);
	if (command->option)
	{
		printf("options:");
		print_double_tab(command->option);
	}
	if (command->arg)
	{
		printf("args:");
		print_double_tab(command->arg);
	}
	if (command->redirection)
	{
		printf("redirections:\t%s\n", command->redirection);
		if (command->output)
			printf("output:\t%s\n", command->output);
	}
	h_pipe(command);
}
