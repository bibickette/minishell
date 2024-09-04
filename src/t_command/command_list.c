#include "minishell.h"

// Ajoute une nouvelle redirection (entrée ou sortie) à un tableau
char **add_redirection(char **redirections, char *redirection, int *size)
{
	char **new_redirections;
	int i = 0;

	new_redirections = ft_calloc(*size + 2, sizeof(char *));
	if (!new_redirections)
		return (NULL);
	while (i < *size)
	{
		new_redirections[i] = redirections[i];
		i++;
	}
	new_redirections[i] = ft_strdup(redirection);
	new_redirections[++i] = NULL;
	(*size)++;
	free(redirections);
	return (new_redirections);
}

// Ajoute un fichier d'entrée ou de sortie
char **add_file(char **files, char *file, int *size)
{
	char **new_files;
	int i = 0;

	new_files = ft_calloc(*size + 2, sizeof(char *));
	if (!new_files)
		return (NULL);
	while (i < *size)
	{
		new_files[i] = files[i];
		i++;
	}
	new_files[i] = ft_strdup(file);
	new_files[++i] = NULL;
	(*size)++;
	free(files);
	return (new_files);
}

// Gère les redirections et pipes en fonction du type des tokens
void	process_redirection_and_pipe(t_list **actual, t_token **actual_content, t_command *content)
{
	int input_size = 0;
	int output_size = 0;
	int redir_size = 0;

	while (*actual)
	{
		// Gestion des redirections de sortie
		if ((*actual_content)->type == OUT_REDIR_TYPE || (*actual_content)->type == APPEND_FILE_TYPE)
		{
			// Ajout du type de redirection et du fichier de sortie
			content->redirections = add_redirection(content->redirections, (*actual_content)->str, &redir_size);
			increment_actual(actual, actual_content); // Passer au fichier de sortie
			if (*actual && (*actual_content)->type == OUTFILE_TYPE)
			{
				content->outputs = add_file(content->outputs, (*actual_content)->str, &output_size);
				increment_actual(actual, actual_content); // Incrément après avoir traité le fichier
			}
		}
		// Gestion des redirections d'entrée
		else if ((*actual_content)->type == IN_REDIR_TYPE)
		{
			// Ajout du type de redirection et du fichier d'entrée
			content->redirections = add_redirection(content->redirections, (*actual_content)->str, &redir_size);
			increment_actual(actual, actual_content); // Passer au fichier d'entrée
			if (*actual && (*actual_content)->type == INFILE_TYPE)
			{
				content->inputs = add_file(content->inputs, (*actual_content)->str, &input_size);
				increment_actual(actual, actual_content); // Incrément après avoir traité le fichier
			}
		}
		else if ((*actual_content)->type == PIPE_TYPE) // Si c'est un pipe
		{
			content->pipe = 1;
			increment_actual(actual, actual_content); // Passe au token suivant après le pipe
			break; // Arrête la boucle si on rencontre un pipe (fin de la commande actuelle)
		}
		else
		{
			break; // Sortir de la boucle si ce n'est ni redirection ni pipe
		}
	}
}

t_list	*command_listing(t_list *token)
{
	t_list		*actual;
	t_list		*command_list;
	t_token		*actual_content;
	t_command	*content;

	if (!token)
		return (NULL);
	actual = token;
	command_list = NULL;
	actual_content = actual->content;
	while (actual)
	{
		content = ft_calloc(1, sizeof(t_command));
		if (!content)
			return (NULL);
		
		if (actual_content->type == CMD_TYPE) // Si c'est une commande
		{
			process_command(&actual, &actual_content, content);
		}

		if (actual)
		{
			process_arguments_and_options(&actual, &actual_content, content); // Gère les options et arguments
		}
		if (actual)
		{
			process_redirection_and_pipe(&actual, &actual_content, content); // Gère les redirections et pipes
		}
		if (!command_list)
			command_list = ft_lstnew_libft(content);
		else
			ft_lstadd_back_libft(&command_list, ft_lstnew_libft(content));
		increment_actual(&actual, &actual_content);
	}
	return (command_list);
}
