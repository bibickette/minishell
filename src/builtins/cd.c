/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 11:55:32 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/20 21:40:36 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env_vars(char *old_pwd, char *new_pwd)
{
	if (setenv("OLDPWD", old_pwd, 1) != 0)
	{
		perror("setenv");
		free(old_pwd);
		free(new_pwd);
		return (KO);
	}
	if (setenv("PWD", new_pwd, 1) != 0)
	{
		perror("setenv");
		free(old_pwd);
		free(new_pwd);
		return (KO);
	}
	free(old_pwd);
	free(new_pwd);
	return (OK);
}

static char	*get_old_pwd(void)
{
	char	*old_pwd;

	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
	{
		perror("getcwd");
		return (NULL);
	}
	return (old_pwd);
}

static int	handle_special_char(char **new_path, char **old_pwd, char **path)
{
	if (!(*path) || ft_strcmp(*path, "~") == 0)
	{
		*new_path = getenv("HOME");
		if (!(*new_path))
		{
			ft_putstr_fd("HOME not set\n", STDERR_FILENO);
			free(*old_pwd);
			return (1);
		}
	}
	else if (ft_strcmp(*path, "-") == 0)
	{
		*new_path = getenv("OLDPWD");
		if (!(*new_path))
		{
			ft_putstr_fd("OLDPWD not set\n", STDERR_FILENO);
			free(*old_pwd);
			return (1);
		}
		ft_putstr_fd(*new_path, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
	}
	return (0);
}

int	cd_cmd(char *path)
{
	char	*old_pwd;
	char	*new_path;
	char	*new_pwd;

	old_pwd = get_old_pwd();
	if (!old_pwd)
		return (KO);
	new_path = path;
	if (handle_special_char(&new_path, &old_pwd, &path) == 1)
		return (KO);
	if (chdir(new_path) != 0)
	{
		perror("cd");
		return (free(old_pwd), KO);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		perror("getcwd");
		free(old_pwd);
		return (KO);
	}
	if (update_env_vars(old_pwd, new_pwd) == KO)
		return (KO);
	return (OK);
}
