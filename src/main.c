/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:18:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/06 18:41:04 by phwang           ###   ########.fr       */
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

	if (check_args(argc, argv) != 0)
		return (1);
	if (init_minishell(&minishell) == KO || get_env(minishell, env) == KO)
		return (apocalypse(minishell), 1);
	export_cmd_w_arg("prout=", minishell);
	export_cmd_w_arg("pouet=lala", minishell);
	export_cmd_w_arg("chips=kk", minishell);
	export_cmd_w_arg("chips", minishell);
	export_cmd_no_arg(minishell->builtins->export);
	env_cmd(minishell->builtins->env);
	// prompt(minishell->token, minishell);
	return (0);
}
