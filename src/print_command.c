/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hexplor <hexplor@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:20:01 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/06 14:27:42 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Fonction pour afficher les tableaux d'arguments ou d'options
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

static void	print_redirections(char **redirections, char **files, const char *type)
{
	int	i;

	i = 0;
	if (redirections && files)
	{
		printf("%s:\n", type);
		while (redirections[i] && files[i])
		{
			printf("\t%s %s\n", redirections[i], files[i]);  // Affiche simplement redirection et fichier
			i++;
		}
	}
}

void	print_command(void *content)
{
	t_command	*command;

	if (!content)
		return ;
	command = (t_command *)content;

	// Affiche la commande principale
	if (command->command)
		printf("command:\t%s\n", command->command);

	// Affiche les options
	if (command->option)
	{
		printf("options:");
		print_double_tab(command->option);
	}

	// Affiche les arguments
	if (command->arg)
	{
		printf("args:");
		print_double_tab(command->arg);
	}

	// Affiche les redirections de sortie
	if (command->redirections && command->outputs)
	{
		print_redirections(command->redirections, command->outputs, "output redirections");
	}

	// Affiche les redirections d'entrée
	if (command->redirections && command->inputs)
	{
		print_redirections(command->redirections, command->inputs, "input redirections");
	}

	// Affiche si la commande est liée par un pipe
	h_pipe(command);
}
