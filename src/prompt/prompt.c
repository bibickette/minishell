/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/14 16:07:02 by yantoine         ###   ########.fr       */
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
		if (ft_strlen(prompt) > 0 && tokenize(prompt, &token) != KO)
		{
			if (token)
			{
				dupplicate_list(token, &minishell->brut_list);
				set_index_again(token, minishell->brut_list);
				expand_everything(minishell, token);
				separate_if_needed(minishell, token);
				start_join_token_if_needed(token, prompt, minishell->brut_list);
				first_token_is_exit(prompt, minishell, token);
				set_token_type(token);
				reset_cmd_pipe(token);
				if (lf_spechar_list(minishell, token) == OK
					&& check_token_operator_order(token, minishell) == OK)
				{
					take_all_files(minishell, token);
					minishell->command_list = command_listing(token);
					set_entire_command(minishell->command_list);
					minishell->command = double_tab_command(minishell->command_list);
					if (minishell->command[1])
						execve_pipe(minishell, token);
					else
						execve_one_cmd(minishell, minishell->command[0], token);
					handle_file_hd(minishell);
					free_files_tab(minishell, minishell->files);
					free_command_list(minishell->command_list, minishell);
					free(minishell->command);
				}
			}
		}
		ft_lstclear_custom(&token, free);
		ft_lstclear_custom(&minishell->brut_list, free);
		free(prompt);
	}
}

/*
note sur env et export :
si la variable na pas	de = alors elle ne sera pas intégré dans env
elle le sera seulement dans export
export display "declare -x " avant chaque case de lenv

si la variable a		un = et rien apres alors elle est export dans env et export
elle est export dans export avec var=""

si le premier char cest =, renvoyer erreur ; ca fait un last status = 1

*/
