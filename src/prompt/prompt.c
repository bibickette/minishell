/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/03 14:15:51 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_list *token, t_data *minishell)
{
	char	*prompt;

	handle_signals();
	prompt = NULL;
	display_intro();
	while (1)
	{
		prompt = get_prompt(&minishell);
		if (!prompt || ft_strcmp(prompt, "exit") == 0)
			handle_exit(minishell, prompt, token);
		else if (ft_strcmp(prompt, "history") == 0)
			display_history(minishell);
		else if (tokenize(prompt, &token) != KO)
		{
			dupplicate_list(token, &minishell->brut_list);
			expand_everything(minishell, token);
			start_join_token_if_needed(token, prompt, minishell->brut_list);
			set_token_type(token);
			if (check_token_operator_order(token, minishell) == OK)
			{
				take_all_files(minishell, token);
				print_all_files(minishell->files);
				close_all_files(minishell->files);
				ft_lstiter(token, print_token);
				minishell->command_list = command_listing(token);
				ft_lstiter(minishell->command_list, print_command);
				printf("la commande s'execute ICI\n");
				free_files_tab(minishell, minishell->files);
				free_command_list(minishell->command_list);
			}
		}
		ft_lstclear_custom(&token, free);
		ft_lstclear_custom(&minishell->brut_list, free);
		free(prompt);
	}
}
void print_all_files(t_file *files)
{
	int i = -1;
	if(!files)
		return;
	while (files[++i].name)
	{
		printf("file name : %s\n", files[i].name);
		printf("file type : %d\n", files[i].type);
		printf("file is open : %d\n", files[i].is_open);
		printf("file fd open : %d\n", files[i].fd);
	}

}

void close_all_files(t_file *files)
{
	int i = -1;
	if(!files)
		return;
	while (files[++i].name)
	{
		close_one_fd(files[i].fd);
		files[i].is_open = KO;
	}
}
/*
note sur env et export :
si la variable na pas de = alors elle ne sera pas intégré dans env
elle le sera seulement dans export
export display "declare -x " avant chaque case de lenv

si la variable a un = et rien apres alors elle est export dans env et export
elle est export dans export avec var=""

si le premier char cest =, renvoyer erreur ; ca fait un last status = 1

*/