/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 20:45:29 by phwang            #+#    #+#             */
/*   Updated: 2024/06/17 17:26:57 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex_bonus.h"

int	create_cmd_bonus(t_pipex *pipex, int argc, char **argv)
{
	int	i;

	i = -1;
	pipex->cmds = ft_calloc((argc - (2 + pipex->here_doc)), sizeof(char *));
	if (!pipex->cmds)
		return (return_err_msg(MALLOC_ERROR));
	while (++i + 3 + pipex->here_doc < argc)
	{
		pipex->cmds[i] = ft_strdup(argv[2 + pipex->here_doc + i]);
		if (!pipex->cmds[i])
			return (return_err_msg(MALLOC_ERROR));
	}
	pipex->cmds[i] = 0;
	pipex->nb_cmds = i;
	return (pid_pipe_tab_create(pipex));
}

int	get_cmds_bonus(int argc, char **argv, t_pipex *pipex)
{
	if (argc < 5)
		return (return_err_msg(ARGC_ERR));
	if (ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])) == 0)
	{
		pipex->here_doc = 1;
		if (argc < 6)
			return (return_err_msg(ARGC_ERR));
		handle_heredoc(argv);
		argv[1] = HERE_DOC;
	}
	check_infile(argv[1], pipex);
	check_outfile(argv[argc - 1], pipex);
	if (create_cmd_bonus(pipex, argc, argv) == ERROR
		|| create_cmd_path(pipex) == ERROR)
		return (ERROR);
	return (cmd_exist(pipex, pipex->path, pipex->cmds));
}

void	handle_heredoc(char **argv)
{
	int		fd_doc;
	char	*line;
	char	*limiter;

	limiter = NULL;
	fd_doc = open(HERE_DOC, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_doc == -1)
		return (ft_putstr_fd(INFILE_ERROR_FD, STDERR_FILENO));
	line = 0;
	limiter = ft_strjoin(argv[2], "\n");
	while (1)
	{
		ft_putstr_fd(HERE_DOC_MSG, STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO, 0);
		if (ft_strncmp(line, limiter, ft_strlen(line)) == 0)
		{
			heredoc_next(line, limiter, fd_doc);
			break ;
		}
		ft_putstr_fd(line, fd_doc);
		free(line);
	}
}

void	heredoc_next(char *line, char *limiter, int fd_heredoc)
{
	close(fd_heredoc);
	free(limiter);
	free(line);
	get_next_line(STDIN_FILENO, 1);
}
