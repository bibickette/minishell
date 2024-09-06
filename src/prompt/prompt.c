/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/06 13:36:34 by phwang           ###   ########.fr       */
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
		if (ft_strcmp(prompt, "history") == 0)
			display_history(minishell);
		else if (ft_strlen(prompt) > 0 && tokenize(prompt, &token) != KO)
		{
			dupplicate_list(token, &minishell->brut_list);
			expand_everything(minishell, token);
			if (lf_spechar_list(minishell, token) == OK)
			{
				start_join_token_if_needed(token, prompt, minishell->brut_list);
				first_token_is_exit(prompt, minishell, token);
				set_token_type(token);
				reset_cmd_pipe(token);
				if (check_token_operator_order(token, minishell) == OK)
				{
					take_all_files(minishell, token);
					// if (minishell->nb_files > 0)
						// print_all_files(minishell->files);
					ft_lstiter(token, print_token);
					minishell->command_list = command_listing(token);
					set_entire_command(minishell->command_list);
					ft_lstiter(minishell->command_list, print_command);
					printf("la commande s'execute ICI\n");
					// execve_one_cmd(minishell, "cat -e", token);
					free_files_tab(minishell, minishell->files);
					free_command_list(minishell->command_list);
					minishell->nb_files = 0;
				}
			}
		}
		ft_lstclear_custom(&token, free);
		ft_lstclear_custom(&minishell->brut_list, free);
		free(prompt);
	}
}

/*
faire un in tab file et out tab file
essayer dopen les files dans le execve, si un in foire, on cree pas le out
*/
