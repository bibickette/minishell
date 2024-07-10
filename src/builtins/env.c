/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 17:43:29 by phwang            #+#    #+#             */
/*   Updated: 2024/07/09 18:09:54 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char *find_path(char *cmd, char **path)
{
	char *path_cmd;
	int i;

	i = -1;
	while(path[++i])
	{
		path_cmd = ft_strjoin(path[i], cmd);
		if (!path_cmd)
		{
			ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO);
			return(NULL);
		}
		if (access(path_cmd, F_OK | X_OK) == 0)
			return(path_cmd);
		free(path_cmd);
	}
	ft_putstr_fd(NO_PATH_ENV, STDERR_FILENO);
	path_cmd = ft_strdup("");
	return(path_cmd);
}

void manual_env_load(t_data *minishell, char **env)
{
	int manual_env_fd;
	int status;
	char *path_env;

	manual_env_fd = open(FILE_ENV, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (manual_env_fd == -1)
	{
		ft_putstr_fd(ERR_ENV, STDERR_FILENO);
		apocalypse(minishell);
	}
	path_env = find_path("env", minishell->path);
	if(ft_strcmp(path_env, "") == 0)
	{
		apocalypse(minishell);
		exit(errno);
	}
	int i = 0;
	// while(env[i])
	// {
	// 	__builtin_printf("%s", env[i]);
	// 	i++;
	// }
	char *other;
	// other = getenv("PATH");
	// printf("%s\n", other);
	// printf("env display end\n");
	execve_one_cmd(path_env, env, manual_env_fd, &status);
	ft_printf("env path = %s\n", path_env);
	if(status != 0)
	{
		apocalypse(minishell);
		exit(status);
	}
	close(manual_env_fd);
	manual_env_fd = open(FILE_ENV, O_RDWR | O_CREAT, 0644);
	char *line;
	while(1)
	{
		line = get_next_line(manual_env_fd, 0);
		if(!line)
			break;
		__builtin_printf("%s", line);
		free(line);
	}
	close(manual_env_fd);
	//excve env
	unlink(FILE_ENV);
}

void execve_one_cmd(char *cmd_path, char **envp, int fd_dest, int *ret)
{
	int pid;
	int status;
	char **arg;

	arg = ft_split(cmd_path, ' ');
	pid = fork();
	if(pid < 0)
	{
		return (ft_putstr_fd(FORK_ERR, STDERR_FILENO));
	}
	if(pid == 0)
	{
		if (dup2(fd_dest, STDOUT_FILENO) == -1)
			exit(errno);
		if(execve(cmd_path, arg, envp) == -1)
		{
			close(fd_dest);
			exit(errno);
		}
		close(fd_dest);
		exit(EXIT_SUCCESS);
	}
	close(fd_dest);
	waitpid(pid, &status, 0);
	*ret = WEXITSTATUS(status);
	if (*ret != 0)
		return (ft_putstr_fd(STATUS_ERR, STDERR_FILENO));
}

void	get_env(t_data *minishell, char **env)
{
	int		env_fd;
	char	*path_env;
	int		i;

	env_fd = open("/etc/environment", O_RDONLY);
	if (env_fd == -1)
		return (ft_putstr_fd(ERR_ENV, STDERR_FILENO));
	path_env = get_next_line(env_fd, 0);
	close(env_fd);
	path_env = ft_strchr(path_env, '/');
	path_env = trim_end(path_env);
	minishell->path = ft_split(path_env, ':');
	if(!minishell->path)
	{
		free(path_env);
		apocalypse(minishell);
		exit(EXIT_JSP);
	}
	// free(path_env);
	i = -1;
	while(minishell->path[++i])
	{
		minishell->path[i] = strjoin_wfree(minishell->path[i], "/");
		if (!minishell->path[i])
		{
			ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO);
			apocalypse(minishell);
			exit(EXIT_JSP);
		}
	}
	return(manual_env_load(minishell, env));
}
