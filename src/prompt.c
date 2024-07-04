/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/04 17:21:38 by yantoine         ###   ########.fr       */
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
		ret = tokenize(prompt, minishell);
		if (ret != OK)
			handle_error(ret, prompt);
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
