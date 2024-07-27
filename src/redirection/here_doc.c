/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:19:41 by phwang            #+#    #+#             */
/*   Updated: 2024/07/27 23:38:30 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_create(t_data *minishell, char *limiter)
{
	int		fd_doc;
	char	*line;
	char	*limiter_tmp;

	limiter_tmp = NULL;
	fd_doc = open(HERE_DOC, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_doc == -1)
		return (ft_putstr_fd(INFILE_ERROR_FD, STDERR_FILENO));
	minishell->here_doc = OK;
	line = 0;
	limiter_tmp = ft_strjoin(limiter, "\n");
	while (1)
	{
		ft_putstr_fd(HERE_DOC_MSG, STDOUT_FILENO);
		line = get_next_line(STDIN_FILENO, 0);
		if(!line)
			return (ft_putstr_fd(HERE_DOC_ERR, STDERR_FILENO));
		if (heredoc_next(line, limiter_tmp, fd_doc) == OK)
			break;
		ft_putstr_fd(line, fd_doc);
		free(line);
	}
}

int	heredoc_next(char *line, char *limiter_tmp, int fd_heredoc)
{
	if (ft_strncmp(line, limiter_tmp, ft_strlen(line)) == 0)
	{
		close(fd_heredoc);
		free(limiter_tmp);
		free(line);
		get_next_line(STDIN_FILENO, 1);
		return(OK);
	}
	return(KO);
}

/*
le here_doc correspond au file <<
le limiter est lelement apres le << , lorsquíl est appelé, ca met fin au here_doc
*/