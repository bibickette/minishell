/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <phwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:43:29 by phwang            #+#    #+#             */
/*   Updated: 2026/02/03 18:32:21 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env(t_data *minishell, char **env)
{
	int	ret;

	if (!env || !env[0] || is_valgrind_env(env) == OK)
		ret = no_environment(minishell);
	else
		ret = load_env(minishell, env);
	return (ret);
}

int	no_environment(t_data *minishell)
{
	int		env_fd;
	char	*path_env;

	path_env = NULL;
	env_fd = open(ROOT_ENV, O_RDONLY);
	if (env_fd == -1)
		return (ft_putstr_fd(ERR_ENV, STDERR_FILENO), KO);
	path_env = get_next_line(env_fd, 0);
	close(env_fd);
	if (!path_env)
		return (ft_putstr_fd(ERR_ENV, STDERR_FILENO), KO);
	return (load_path(minishell, 0, path_env));
}

int	load_env(t_data *minishell, char **env)
{
	int	env_size;
	int	i;

	env_size = 0;
	while (env[env_size])
		env_size++;
	i = -1;
	while (++i < env_size)
		if (char_add_back_tab(&minishell->builtins->env, env[i]) == false)
			return (ft_putstr_fd(ADD_BACK_TAB_ERR, STDERR_FILENO), KO);
	if (handle_shell_level(minishell) == KO || load_export_tab(minishell,
			env) == KO)
		return (KO);
	return (load_path(minishell, 1, NULL));
}

int	load_path(t_data *minishell, int flag, char *path_env)
{
	int		i;
	int		ret;
	char	*path_from_env;

	path_from_env = NULL;
	ret = load_path_from_flag(minishell, flag, &path_from_env, path_env);
	if (ret == KO)
		return (OK);
	else if (ret == M_KO)
		return (KO);
	if (load_right_split(minishell, flag, path_from_env, path_env) == KO)
		return (KO);
	i = -1;
	if (path_from_env)
		free_set_null(&path_from_env);
	if (flag != 2 && path_env)
		free_set_null(&path_env);
	while (minishell->path[++i])
	{
		minishell->path[i] = strjoin_wfree(minishell->path[i], "/");
		if (!minishell->path[i])
			return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
	}
	return (OK);
}
