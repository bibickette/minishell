/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:48:50 by phwang            #+#    #+#             */
/*   Updated: 2024/06/17 17:08:10 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (get_env_path(argc, argv, env, &pipex) == ERROR || get_cmds_bonus(argc,
			argv, &pipex) == ERROR)
	{
		free_all(&pipex);
		exit(EXIT_FAILURE);
	}
	do_pipex(&pipex, env);
	if (pipex.here_doc == 1)
		unlink(HERE_DOC);
	return (0);
}
