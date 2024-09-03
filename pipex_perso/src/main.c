/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:59:56 by phwang            #+#    #+#             */
/*   Updated: 2024/06/17 17:08:06 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (get_env_path(argc, argv, env, &pipex) == ERROR || get_cmds(argc, argv,
			&pipex) == ERROR)
	{
		free_all(&pipex);
		exit(EXIT_FAILURE);
	}
	do_pipex(&pipex, env);
	return (0);
}
// ./pipex infile "ls -l" "wc -l" outfile
// < infile ls -l | wc -l > outfile
