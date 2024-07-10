/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:18:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/09 17:24:01 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
	Le main de notre minishell, qui va afficher le prompt et 
	etre en attente de commande d'utilisateur
	
	Le prompt est affiché avec la fonction display_prompt

	TOUT SUGGESTION DE MODIFICATION EST LA BIENVENUE
*/

int	main(int argc, char **argv, char **env)
{
	t_data	*minishell;

	if(init_minishell(&minishell) == KO)
		apocalypse(minishell);
	if (check_args(argc, argv) != 0)
		return (1);
	get_env(minishell, env);
	prompt(minishell->token, minishell);
	return (0);
}
