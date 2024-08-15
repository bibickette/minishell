/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 19:18:52 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/15 16:04:11 by phwang           ###   ########.fr       */
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
	printf("----\n");
	export_cmd(&minishell->builtins->export, "paprika=PAVUPAPRI KA", minishell);
	printf("----\n");
	char tab[] =  "ouet=\"prout phrase$paprika avec $USER.";
	tab[ft_strlen(tab) - 1] = '"';
	export_cmd(&minishell->builtins->export, tab, minishell);
	printf("----\n");
	export_cmd(&minishell->builtins->export, "kiki='prout phrase $var avec $USER'", minishell);
	export_cmd(&minishell->builtins->export, "paprika=PROUT KA", minishell);
	printf("----\n");
	printf("\nexport 1 ----\n");
	// env_cmd_check_export(minishell->builtins->export);
	env_cmd(minishell->builtins->env, minishell->builtins->export);
	printf("\nexport 2 ----\n");
	unset_cmd(minishell->builtins, "paprika");
	unset_cmd(minishell->builtins, "ouet");
	unset_cmd(minishell->builtins, "chips");
	env_cmd_check_export(minishell->builtins->export);
	apocalypse(minishell);
	// prompt(minishell->token, minishell);
	return (0);
}
