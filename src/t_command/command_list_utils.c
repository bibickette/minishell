#include "minishell.h"

void	process_arguments_and_options(t_list **actual, t_token **actual_content, t_command *content)
{
	int	arg_size = 0;
	int	opt_size = 0;

	while (*actual)
	{
		if ((*actual_content)->type == ARG_TYPE) // Si c'est un argument
		{
			content->arg = add_argument(content->arg, (*actual_content)->str, &arg_size);
		}
		else if ((*actual_content)->type == OPT_TYPE) // Si c'est une option
		{
			content->option = add_option(content->option, (*actual_content)->str, &opt_size);
		}
		else
		{
			break;
		}
		increment_actual(actual, actual_content);
	}
}

// Incrémente le pointeur sur l'élément actuel
void	increment_actual(t_list **actual, t_token **actual_content)
{
	if (*actual)
		*actual = (*actual)->next;
	if (*actual)
		*actual_content = (*actual)->content;
}

// Ajoute une option en fonction du type
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

// Ajoute un argument en fonction du type
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

// Traite la commande principale
void	process_command(t_list **actual, t_token **actual_content, t_command *content)
{
	if ((*actual_content)->type != CMD_TYPE)
		return ;
	content->command = ft_strdup((*actual_content)->str);
	increment_actual(actual, actual_content);
}
