/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 23:03:04 by phwang            #+#    #+#             */
/*   Updated: 2024/06/17 17:25:26 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	get_env_path(int argc, char **argv, char **env, t_pipex *pipex)
{
	int	path_line;
	int	i;

	if (!env)
		exit_error(pipex, ENV_ERROR);
	set_null_struct(pipex);
	path_line = -1;
	while (env[++path_line])
	{
		if (ft_strncmp(env[path_line], PATH, ft_strlen(PATH)) == 0)
		{
			pipex->path = ft_split(ft_strchr(env[path_line], '/'), ':');
			if (!pipex->path)
				return (return_err_msg(MALLOC_ERROR));
			i = -1;
			while (pipex->path[++i])
			{
				pipex->path[i] = strjoin_wfree(pipex->path[i], "/");
				if (!pipex->path[i])
					return (return_err_msg(MALLOC_ERROR));
			}
			return (OK);
		}
	}
	return (check_absolute_path(argv, argc, pipex));
}

int	check_absolute_path(char **argv, int argc, t_pipex *pipex)
{
	int	i;

	i = -1;
	pipex->empty_env = 1;
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
		pipex->here_doc = 1;
	while (++i + 3 + pipex->here_doc < argc)
		if (argv[2 + pipex->here_doc + i][0] == '/')
			return (OK);
	return (return_err_msg(PATH_ERROR));
}

int	get_cmds(int argc, char **argv, t_pipex *pipex)
{
	if (argc != 5)
		return (return_err_msg(ARGC_ERR));
	if (create_cmd(pipex, argc, argv) == ERROR
		|| create_cmd_path(pipex) == ERROR)
		return (ERROR);
	check_infile(argv[1], pipex);
	check_outfile(argv[argc - 1], pipex);
	return (cmd_exist(pipex, pipex->path, pipex->cmds));
}

void	check_infile(char *fd_in, t_pipex *pipex)
{
	if ((access(fd_in, F_OK) == 0) && (access(fd_in, R_OK) == 0))
	{
		pipex->fd_in = open(fd_in, O_RDONLY);
		if (pipex->fd_in == -1)
			ft_putstr_fd(INFILE_ERROR_FD, STDERR_FILENO);
	}
	else if ((access(fd_in, F_OK) == 0) && (access(fd_in, R_OK) != 0))
	{
		perror(PERR_MSG);
		ft_putstr_fd("File error : ", STDERR_FILENO);
		ft_putstr_fd(fd_in, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
		ft_putstr_fd(INFILE_ERROR, STDERR_FILENO);
}

void	check_outfile(char *fd_out, t_pipex *pipex)
{
	if ((access(fd_out, F_OK) == 0) && (access(fd_out, W_OK) != 0))
	{
		perror(PERR_MSG);
		ft_putstr_fd("File error : ", STDERR_FILENO);
		ft_putstr_fd(fd_out, STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	else
	{
		if (pipex->here_doc == 1)
		{
			pipex->fd_out = open(fd_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (pipex->fd_out == -1)
				ft_putstr_fd(OUTFILE_ERROR_FD, STDERR_FILENO);
		}
		else
		{
			pipex->fd_out = open(fd_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (pipex->fd_out == -1)
				ft_putstr_fd(OUTFILE_ERROR_FD, STDERR_FILENO);
		}
	}
}
