/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/23 13:44:33 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_list *token, t_data *minishell)
{
	char	*prompt;
	int	ret;

	handle_signals();
	prompt = NULL;
	display_intro();
	ret = 0;
	while (1)
	{
		prompt = get_prompt(&minishell);
		if (ft_strcmp(prompt, "exit") == 0)
			handle_exit(minishell, prompt, token);
		if (ft_strcmp(prompt, "history") == 0)
			display_history(minishell);
		tokenize(prompt, &token);
		if (check_lexical(token) == 0)
		{
			printf("minishell: syntax error\n");
			ft_lstclear_custom(&token, free);
			free(prompt);
		}
		else
		{
			minishell->command_list = command_listing(token, &ret);
			if (ret != 1)
			{
				printf("la commande s'execute ICI\n");
			}
			ft_lstiter(token, print_token);
			ft_lstiter(minishell->command_list, print_command);
			ft_lstclear_custom(&token, free);
			free(prompt);
		}
	}
}
