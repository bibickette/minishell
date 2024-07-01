/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:18:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/01 20:10:48 by yantoine         ###   ########.fr       */
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
	t_data	minishell;

	ft_bzero(minishell, sizeof(t_data));
	if (check_args(argc, argv) != 0)
		return (1);
	prompt(&minishell);
	return (0);
}
