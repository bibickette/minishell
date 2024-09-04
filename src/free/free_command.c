#include "minishell.h"

// Fonction pour libérer un tableau de chaînes de caractères
static void	free_double_tab(char **tab)
{
	int i = 0;

	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

// Fonction pour libérer une commande
void	free_command(t_command *command)
{
	if (!command)
		return ;

	// Libère la commande principale
	if (command->command)
		free(command->command);

	// Libère les options
	free_double_tab(command->option);

	// Libère les arguments
	free_double_tab(command->arg);

	// Libère les fichiers de sortie et redirections associées
	free_double_tab(command->outputs);
	free_double_tab(command->redirections);

	// Libère les fichiers d'entrée
	free_double_tab(command->inputs);

	// Libère la commande entière si elle est stockée
	if (command->entire_command)
		free(command->entire_command);

	// Libère enfin la structure de la commande elle-même
	free(command);
}

// Fonction pour libérer la liste chaînée de commandes
void	free_command_list(t_list *command_list)
{
	t_list	*tmp;

	while (command_list)
	{
		tmp = command_list->next;
		free_command((t_command *)command_list->content);
		free(command_list);
		command_list = tmp;
	}
}
