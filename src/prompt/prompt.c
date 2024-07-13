/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/13 02:52:28 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_list *token, t_data *minishell)
{
	int		ret;
	char	*prompt;

	handle_signals();
	prompt = NULL;
	display_intro();
	while (1)
	{
		display_prompt();
		prompt = get_prompt();
		if (ft_strcmp(prompt, "exit\n") == 0)
			handle_exit(minishell, prompt, token);
		ret = tokenize(prompt, &token);
		if (ret != OK)
			handle_error(ret, prompt);
		ft_lstiter(token, print_token);
		ft_lstclear_custom(&token, free);
		free(prompt);
	}
}
/* 
exit doit exit un status
*/
