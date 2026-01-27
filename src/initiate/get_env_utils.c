/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 18:12:09 by phwang            #+#    #+#             */
/*   Updated: 2024/09/29 18:13:33 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	load_path_from_flag(t_data *minishell, int flag, char **path_from_env,
		char *path_env)
{
	if (flag != 0)
		if (load_value(minishell, "PATH=", path_from_env, path_env) == KO)
			return (M_KO);
	if (flag == 2 && has_path(*path_from_env) == KO)
	{
		if (char_add_back_tab(&minishell->path, *path_from_env) == KO)
			return (M_KO);
		return (free_set_null(path_from_env), KO);
	}
	return (OK);
}

int	load_right_split(t_data *minishell, int flag, char *path_from_env,
		char *path_env)
{
	if (flag != 0)
		minishell->path = ft_split(trim_end(ft_strchr(path_from_env, '/')),
				':');
	else
		minishell->path = ft_split(trim_end(ft_strchr(path_env, '/')), ':');
	if (!minishell->path)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	return (OK);
}
