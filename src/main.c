/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:18:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/23 14:26:55 by yantoine         ###   ########.fr       */
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
	(void)env;
	(void)argv;
	if (check_args(argc, argv) != 0)
		return (1);
	display_prompt();
	return (0);
}
