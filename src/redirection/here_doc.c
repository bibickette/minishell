/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:19:41 by phwang            #+#    #+#             */
/*   Updated: 2024/09/19 00:03:59 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// extern volatile sig_atomic_t g_signal;

void	heredoc_create(t_data *minishell, char *limiter)
{
	int		fd_doc;
	char	*line;
	char	*limiter_tmp;
	int std_in = dup(STDIN_FILENO);
	int std_inb = dup(STDIN_FILENO);

	limiter_tmp = NULL;
	fd_doc = open(HERE_DOC, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd_doc == -1)
		return (ft_putstr_fd(INFILE_ERROR_FD, STDERR_FILENO));
	minishell->here_doc = OK;
	line = 0;
	limiter_tmp = ft_strjoin(limiter, "\n");
	if (!limiter_tmp)
		return (ft_putstr_fd(STRJOIN_ERR, STDERR_FILENO));
	dup2(std_in, STDIN_FILENO);
	while (1)
	{
		// g_signal = IN_HD;
		line = readline(HERE_DOC_MSG);
		if (!line)
		{
			close(std_inb);
			close(std_in);
			close(fd_doc);
			free_n_set_var_null(&limiter_tmp);
			return (ft_putstr_fd(HERE_DOC_ERR, STDERR_FILENO));
		}
		if (heredoc_next(line, limiter_tmp, fd_doc) == OK)
		{
			close(std_in);
			dup2(std_inb, STDIN_FILENO);
			close(std_inb);
			break ;
		}
		ft_putstr_fd(line, fd_doc);
		ft_putstr_fd("\n", fd_doc);
		free(line);
		line = 0;
	}
}

int	heredoc_next(char *line, char *limiter_tmp, int fd_heredoc)
{
	if (ft_strncmp(line, limiter_tmp, ft_strlen(line)) == 0)
	{
		close(STDIN_FILENO);
		close(fd_heredoc);
		free_n_set_var_null(&limiter_tmp);
		free_n_set_var_null(&line);
		return (OK);
	}
	return (KO);
}

/*
le here_doc correspond au file <<
le limiter est lelement apres le << , lorsquíl est appelé,
	ca met fin au here_doc
*/

void	handle_file_hd(t_data *minishell)
{
	if (minishell->here_doc == OK)
	{
		if (unlink(HERE_DOC) < 0)
		{
			perror(UNLINK_ERR);
			minishell->last_status = errno;
		}
		minishell->here_doc = KO;
	}
}
