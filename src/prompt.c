/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/05 20:19:35 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(t_list *minishell)
{
	int		ret;
	char	*prompt;

	prompt = NULL;
	display_intro();
	while (1)
	{
		display_prompt();
		prompt = get_prompt();
		if (ft_strcmp(prompt, "exit\n") == 0)
		{
			free(prompt);
			free(minishell);
			get_next_line(0, 1);
			return ;
		}
		ret = tokenize(prompt, &minishell);
		if (ret != OK)
			handle_error(ret, prompt);
		ft_lstiter(minishell, print_token);
		ft_lstclear_custom(&minishell, free);
		free(prompt);
	}
}
/* ceci est juste un test

 on a besoin que si on recoit signal 2 SIGINT = ctrl C
 ca doit free tout le programme 

 le flag 1 de gnl sert a free le buffer, le flag 0 fait rien
 pour linstant ctrl D ne fait aucun leak

 exit doit exit un status
*/
