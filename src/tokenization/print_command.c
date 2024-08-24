/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:29:48 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/24 17:15:28 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_double_tab(char **tab)
{
	int i;

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

void	print_command(void *content)
{
	t_command	*command;

	if (!content)
		return;
	command = (t_command *)content;
	if (command->command)
		printf("command:\t%s\n", command->command);
	else
		printf("command:\t(NULL)\n");
	printf("options:");
	print_double_tab(command->option);
	printf("args:");
	print_double_tab(command->arg);
	if (command->redirection)
	{
		printf("redirections:\t%s\n", command->redirection);
		if (command->output)
			printf("output:\t%s\n", command->output);
		else
			printf("output:\t(NULL)\n");
	}
	else
		printf("redirections:\t(NULL)\n");
	if (command->pipe)
		printf("pipe: yes\n");
	else
		printf("pipe: no\n");
}

