#include "minishell.h"

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

void	process_redirection_and_pipe(t_list **actual, t_token **actual_content, t_command *content)
{
	int input_size = 0;
	int output_size = 0;
	int redir_size = 0;

	while (*actual)
	{
		if ((*actual_content)->type == OUT_REDIR_TYPE || (*actual_content)->type == HD_APPEND_TYPE)
		{
			content->redirections = add_redirection(content->redirections, (*actual_content)->str, &redir_size);
			increment_actual(actual, actual_content);
			if (*actual && (*actual_content)->type == OUTFILE_TYPE)
				content->outputs = add_file(content->outputs, (*actual_content)->str, &output_size);
		}
		else if ((*actual_content)->type == IN_REDIR_TYPE || (*actual_content)->type == HERE_DOC_TYPE)
		{
			content->redirections = add_redirection(content->redirections, (*actual_content)->str, &redir_size);
			increment_actual(actual, actual_content);
			if (*actual && (*actual_content)->type == INFILE_TYPE)
				content->inputs = add_file(content->inputs, (*actual_content)->str, &input_size);
		}
		else if ((*actual_content)->type == PIPE_TYPE)
		{
			content->pipe = 1;
			break;
		}
		else
			break; 
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
		while (1)
		{
			if (!content)
				return (NULL);
			else if (actual_content->type == CMD_TYPE || actual_content->type == BUILTIN_TYPE)
				process_command(&actual, &actual_content, content);
			else if (actual && (actual_content->type == ARG_TYPE || actual_content->type == OPT_TYPE))
				process_arguments_and_options(&actual, &actual_content, content);
			else if (actual && (actual_content->type == IN_REDIR_TYPE || actual_content->type == OUT_REDIR_TYPE || \
							actual_content->type == HERE_DOC_TYPE || actual_content->type == HD_APPEND_TYPE || actual_content->type == PIPE_TYPE))
				process_redirection_and_pipe(&actual, &actual_content, content);
			else if (!command_list && (actual_content->type == CMD_TYPE || actual_content->type == BUILTIN_TYPE))
				command_list = ft_lstnew_libft(content);
			if (!actual || actual_content->type == PIPE_TYPE)
				break;
			increment_actual(&actual, &actual_content);
		}
		ft_lstadd_back_libft(&command_list, ft_lstnew_libft(content));
		increment_actual(&actual, &actual_content);
	}
	return (command_list);
}
