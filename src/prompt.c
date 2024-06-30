/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/30 16:53:06 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	prompt(void)
{
	char	***commands;
	char	*prompt;

	prompt = NULL;
	display_intro();
	while (1)
	{
		display_prompt();
		prompt = get_prompt();
		commands = parsing_prompt(prompt);
		free_double_char(commands);
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
