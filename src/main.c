/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:18:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/23 00:12:23 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
	Le main de notre minishell, qui va afficher le prompt et 
	etre en attente de commande d'utilisateur
	
	Le prompt est affiché avec la fonction display_prompt

	TOUT SUGGESTION DE MODIFICATION EST LA BIENVENUE
*/

int	main(int argc, char **argv, char **env)
{
	if (argc != 1) // jsp on est censé faire quoi
	{
		ft_putstr_fd("Error: too many arguments\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	display_prompt();
	return (0);
}

// DSL POUR LES INCLUDES MANUEL JARRIVE PAS A INCLUDE LE HEADER DANS LE MAKEFILE