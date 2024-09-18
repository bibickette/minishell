/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/18 21:48:46 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_list *token, t_data *minishell)
{
	char	*prompt;

	prompt = NULL;
	display_intro();
	while (1)
	{
		prompt = get_prompt(&minishell);
		handle_signals(minishell);
		if (ft_strlen(prompt) > 0 && tokenize(prompt, &token) != KO)
			if (token)
				if (the_parser_set(token, minishell, prompt) == OK
					&& lf_spechar_list(minishell, token) == OK
					&& check_token_operator_order(token, minishell) == OK)
					the_execution(token, minishell);
		ft_lstclear_custom(&token, free);
		ft_lstclear_custom(&minishell->brut_list, free);
		free(prompt);
	}
}

int	the_parser_set(t_list *token, t_data *minishell, char *prompt)
{
	if (dupplicate_list(token, &minishell->brut_list) == KO)
		return (KO);
	set_index_again(token, minishell->brut_list);
	if (expand_everything(minishell, token) == KO)
		return (KO);
	if (separate_if_needed(minishell, token) == KO)
		return (KO);
	if (start_join_token_if_needed(token, prompt, minishell->brut_list) == KO)
		return (KO);
	first_token_is_exit(prompt, minishell, token);
	set_token_type(token);
	reset_cmd_pipe(token);
	return (OK);
}

void	the_execution(t_list *token, t_data *minishell)
{
	if (take_all_files(minishell, token) == KO)
		return ;
	if (open_all_hd_file(minishell) == KO)
	{
		minishell->last_status = errno;
		free_files_tab(minishell, minishell->files);
		return ;
	}
	build_cmd_tab(minishell, token);
	if (minishell->nb_cmd == 1 && minishell->command_tab)
		execve_one_cmd(minishell, token);
	else if (minishell->command_tab)
		execve_pipe(minishell, token);
	if (minishell->nb_files > 1)
		close_all_files(minishell->files);
	free_files_tab(minishell, minishell->files);
	free_double_char(&minishell->command_tab);
	free_double_char(&minishell->cmd_original);
	handle_file_hd(minishell);
}
