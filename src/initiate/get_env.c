/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:43:29 by phwang            #+#    #+#             */
/*   Updated: 2024/09/06 15:46:15 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_env(t_data *minishell, char **env)
{
	int	ret;

	if (!env || !env[0])
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
	return (load_path(minishell, 0));
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
		if (char_add_back_tab(&minishell->builtins->env, env[i]) == KO)
			return (ft_putstr_fd(ADD_BACK_TAB_ERR, STDERR_FILENO), KO);
	if (load_export_tab(minishell, env) == KO)
		return (KO);
	return (load_path(minishell, 1));
}

int	load_path(t_data *minishell, int flag)
{
	char	*path_env;
	int		i;

	if (flag == 1)
	{
		path_env = getenv("PATH");
		if (!path_env)
			return (ft_putstr_fd(ERR_PATH, STDERR_FILENO), KO);
	}
	minishell->path = ft_split(trim_end(ft_strchr(path_env, '/')), ':');
	if (!minishell->path)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	i = -1;
	while (minishell->path[++i])
	{
		minishell->path[i] = strjoin_wfree(minishell->path[i], "/");
		if (!minishell->path[i])
			return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO), KO);
	}
	return (OK);
}

char	*trim_end(char *path_env)
{
	int	len;

	if (!path_env)
		return (NULL);
	len = ft_strlen(path_env);
	if (path_env[len - 2] == 34)
		path_env[len - 2] = '\0';
	return (path_env);
}
