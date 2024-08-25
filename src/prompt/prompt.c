/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/25 14:36:42 by phwang           ###   ########.fr       */
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
		tokenize(prompt, &token);
		set_token_type(token);
		ft_lstiter(token, print_token);
		// expand_everything(minishell, token);
		minishell->command_list = command_listing(token);
		ft_lstiter(minishell->command_list, print_command);
		printf("la commande s'execute ICI\n");
		free_command_list(minishell->command_list);
		ft_lstclear_custom(&token, free);
		free(prompt);
	}
}

void expand_everything(t_data *minishell, t_list *token)
{
	t_list *tmp_head;

	tmp_head = token;
	while(tmp_head)
	{
		if(((t_token *)tmp_head->content)->quote != S_QUOTE)
		{
			char *str_expanded;
			char	**expanded_exported;
			str_expanded = ft_strdup(((t_token *)tmp_head->content)->str);
			if(!str_expanded)
				return(ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO));
			expanded_exported = ft_split(str_expanded, ' ');
			if (!expanded_exported)
				return(ft_putstr_fd(EXPORT_MALLOC_ERR, STDERR_FILENO));
			// au dessus, separe la string dans des tabs, copie loriginal du token
			char	*dollar;
			int		y;
			y = -1;
			
		}
		if(tmp_head->next == NULL)
			break;
		tmp_head = tmp_head->next;
	}
}
