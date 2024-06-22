/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:33:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/23 00:21:17 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Affiche le prompt de notre minishell
*/

void	display_prompt(void)
{
	char *prompt;
	prompt = NULL;
	ft_putstr_fd("Bienvenue dans baby Minishell :D\n", STDOUT_FILENO); // fun
	while (1)
	{
		ft_putstr_fd("minishell $> ", STDOUT_FILENO);
		prompt = get_next_line(STDIN_FILENO, 0);
		if (!prompt)
		{
			apocalypse();
			exit(EXIT_FAILURE); //jsp encore
		}
		if(ft_strncmp(prompt, "exit\n", ft_strlen(prompt)) == 0) 
		{
			// bah je suppose que exit tout seul ca doit exit le prog
			free(prompt);
			apocalypse();
			exit(0);
		}
		// la tokenisation et le debut de read la ligne pour faire des trucs
		// doit commencer ici, je pense
		free(prompt);
	}
}

// ceci est juste un test

// on a besoin que si on recoit signal 2 SIGINT = ctrl C
// ca doit free tout le programme

// le flag 1 de gnl sert a free le buffer, le flag 0 fait rien
// pour linstant ctrl D ne fait aucun leak

// exit doit exit un status