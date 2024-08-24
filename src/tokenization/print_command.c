/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 13:29:48 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/23 13:45:44 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
static void	print_double_tab(char tab[50][50])
{
	int	i;

	i = 0;
	while (tab[i] || i == 50)
	{
		printf("\t%s\n", tab[i]);
		i++;
	}
}
*/
void	print_command(void *content)
{
	t_command *command;

	command = (t_command *)content;
	printf("command: %p\n", command->command);
	printf("command: %s\n", command->command);
/*	
	printf("command: %s\n", command->command);
	printf("options:\n");
	print_double_tab(command->option);
	printf("args:\n");
	print_double_tab(command->arg);
	printf("redirections: %s\n", command->redirection);
*/
}
