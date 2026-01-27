/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:19:41 by phwang            #+#    #+#             */
/*   Updated: 2024/09/25 00:03:58 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

int	heredoc_create(t_data *minishell, char *limiter)
{
	int	std_in;
	int	std_inb;

	if (init_dup_hd(&std_in, &std_inb) == KO)
		return (KO);
	minishell->fd_hd = open(HERE_DOC, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (minishell->fd_hd == -1)
		return (ft_putstr_fd(INFILE_ERROR_FD, STDERR_FILENO), KO);
	minishell->here_doc = OK;
	if (dup_db_hd(std_in, std_inb, minishell) == KO)
		return (KO);
	while (1)
	{
		g_signal = IN_HD;
		if (heredoc_handler(minishell, std_in, std_inb, limiter) == KO)
			return (KO);
	}
	return (OK);
}

/*
le here_doc correspond au file <<
le limiter est lelement apres le << , lorsquil est appelé,
	ca met fin au here_doc
*/

int	heredoc_handler(t_data *minishell, int std_in, int std_inb, char *limiter)
{
	char	*line;
	char	**dollar_tab;

	line = NULL;
	line = readline(HERE_DOC_MSG);
	if (g_signal == HD_STOP)
		if (handle_no_line_hd(minishell, std_in, std_inb) == KO)
			return (KO);
	if (!line)
	{
		retrieve_norm(minishell);
		return (ft_putstr_fd(HERE_DOC_ERR, STDERR_FILENO),
			close_one_fd(std_inb), close_one_fd(std_in), KO);
	}
	if (line[0] && heredoc_next(line, limiter, minishell->fd_hd) == OK)
	{
		close_one_fd(std_in);
		if (dup2(std_inb, STDIN_FILENO) < 0)
			return (close_one_fd(std_inb), perror(DUP_ERR), KO);
		return (close_one_fd(std_inb), KO);
	}
	if (!line)
		start_expanding(minishell, &dollar_tab, &line);
	ft_putstr_fd(line, minishell->fd_hd);
	return (ft_putstr_fd("\n", minishell->fd_hd), free_set_null(&line), OK);
}

int	heredoc_next(char *line, char *limiter_tmp, int fd_heredoc)
{
	if (ft_strcmp(line, limiter_tmp) == 0)
	{
		close_one_fd(STDIN_FILENO);
		close_one_fd(fd_heredoc);
		free_set_null(&line);
		g_signal = 0;
		return (OK);
	}
	return (KO);
}

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

void	retrieve_norm(t_data *minishell)
{
	g_signal = CTRL_D;
	minishell->last_status = 0;
	close_one_fd(minishell->fd_hd);
}
