/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/30 18:28:33 by phwang           ###   ########.fr       */
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
		if (ft_strcmp(prompt, "exit") == 0)
			handle_exit(minishell, prompt, token);
		if (ft_strcmp(prompt, "history") == 0)
			display_history(minishell);
		if (tokenize(prompt, &token) != KO)
		{
			dupplicate_list(token, &minishell->brut_list);
			expand_everything(minishell, token);
			join_token_if_needed(token, prompt, minishell->brut_list);
			set_token_type(token);
			take_all_files(minishell, token);
			ft_lstiter(token, print_token);
			minishell->command_list = command_listing(token);
			ft_lstiter(minishell->command_list, print_command);
			printf("la commande s'execute ICI\n");
			free_files_tab(minishell, minishell->files);
			free_command_list(minishell->command_list);
		}
		ft_lstclear_custom(&token, free);
		ft_lstclear_custom(&minishell->brut_list, free);
		free(prompt);
	}
}
