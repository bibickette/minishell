/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/02 01:47:01 by phwang           ###   ########.fr       */
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
			if(check_token_operator_order(token, minishell) == OK)
			{
				take_all_files(minishell, token);
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

/*
note sur env et export
si la variable a un =, elle sera integré dans env ET export, sinon seulement dans export
si cest pouet=
dans export ca fera pouet=''
et env pouet=
si il ny a pas de =, ca sera integré dans export avec var=''
si on rentre 2 fois sans =, ca sera integré dans env avec var=

ce qui est rentré apres unset  ou export sont des arguments de export/unset

*/