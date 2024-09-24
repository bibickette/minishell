/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:43:29 by phwang            #+#    #+#             */
/*   Updated: 2024/09/25 00:08:10 by phwang           ###   ########.fr       */
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
		if (char_add_back_tab(&minishell->builtins->env, env[i]) == KO)
			return (ft_putstr_fd(ADD_BACK_TAB_ERR, STDERR_FILENO), KO);
	if (handle_shell_level(minishell) == KO || load_export_tab(minishell,
			env) == KO)
		return (KO);
	return (load_path(minishell, 1, NULL));
}

int	load_path(t_data *minishell, int flag, char *path_env)
{
	int		i;
	char	*path_from_env;

	path_from_env = NULL;
	if (flag != 0)
		if (load_value(minishell, "PATH=", &path_from_env, path_env) == KO)
			return (KO);
	if (flag == 2 && has_path(path_from_env) == KO)
	{
		char_add_back_tab(&minishell->path, path_from_env);
		return (free_set_null(&path_from_env), OK);
	}
	if (flag != 0)
		minishell->path = ft_split(trim_end(ft_strchr(path_from_env, '/')),
				':');
	else
		minishell->path = ft_split(trim_end(ft_strchr(path_env, '/')), ':');
	if (!minishell->path)
		return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
	i = -1;
	if (path_from_env)
		free_set_null(&path_from_env);
	if (path_env)
		free_set_null(&path_env);
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

int	lf_for_char(char **str, char c)
{
	int	i;

	i = -1;
	while ((*str)[++i])
		if ((*str)[i] == c)
			return (OK);
	return (KO);
}

int	load_value(t_data *minishell, char *var, char **to_value, char *cmd_export)
{
	int	i;

	i = -1;
	if (cmd_export)
	{
		if (ft_strncmp(cmd_export, var, ft_strlen(var)) == 0)
		{
			*to_value = ft_strdup(cmd_export + ft_strlen(var));
			if (!*to_value)
				return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
			return (OK);
		}
	}
	while (minishell->builtins->env[++i])
	{
		if (ft_strncmp(minishell->builtins->env[i], var, ft_strlen(var)) == 0)
		{
			*to_value = ft_strdup(minishell->builtins->env[i] + ft_strlen(var));
			if (!*to_value)
				return (ft_putstr_fd(MALLOC_ERR, STDERR_FILENO), KO);
			return (OK);
		}
	}
	return (KO);
}

int	is_valgrind_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strnstr(env[i], "valgrind", ft_strlen(env[i])))
			return (OK);
	}
	return (KO);
}
