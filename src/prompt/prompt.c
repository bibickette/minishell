/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/29 16:31:51 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

void	prompt(t_list *token, t_data *minishell)
{
	display_intro();
	while (1)
	{
		get_prompt(&minishell);
		handle_signals(minishell);
		if (ft_strlen(minishell->prompt) > 0 && tokenize(minishell->prompt,
				&token) != KO)
			if (token)
				if (the_parser_set(token, minishell, minishell->prompt) == OK
					// && lf_spechar_list(minishell, token) == OK
					&& check_token_operator_order(token, minishell) == OK)
					the_execution(token, minishell);
		ft_lstclear_custom(&token, free);
		ft_lstclear_custom(&minishell->brut_list, free);
		free(minishell->prompt);
	}
}

int	the_parser_set(t_list *token, t_data *minishell, char *prompt)
{
	if (dupplicate_list(token, &minishell->brut_list) == KO)
		return (KO);
	set_index_again(token, minishell->brut_list);
	// ft_lstiter(token, print_token);
	if (expand_everything(minishell, token) == KO)
		return (KO);
	if (separate_if_needed(minishell, token) == KO)
		return (KO);
	// printf("----------------`\n");
	// ft_lstiter(token, print_token);
	// ft_lstiter(minishell->brut_list, print_token);
	if (start_join_token_if_needed(token, prompt, minishell->brut_list) == KO)
		return (KO);
	// ft_lstiter(token, print_token);
	set_token_type(token);
	reset_cmd_pipe(token);
	return (OK);
}

void	the_execution(t_list *token, t_data *minishell)
{
	if (take_all_hd_files(minishell, token) == KO)
		return ;
	here_doc_create_all(minishell);
	init_cmd_list(minishell, token);
	handle_signals(minishell);
	// signal(SIGQUIT, handle_sigquit);
	// if (minishell->nb_cmd == 1)
	// 	execve_one_cmd(minishell, token);
	// else if (minishell->nb_cmd > 1)
	// 	execve_pipe(minishell, token);
	// signal(SIGQUIT, SIG_IGN);
	if (!(g_signal == WAS_IN_HD))
		g_signal = 0;
	if (minishell->nb_hd_files > 0)
		close_all_files(minishell->files);
	ft_lstclear_custom_cmd(&minishell->list_cmd, free);
	free_files_tab(minishell, minishell->files);
	handle_file_hd(minishell);
}
