/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 23:19:41 by phwang            #+#    #+#             */
/*   Updated: 2024/09/19 14:47:01 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern volatile sig_atomic_t	g_signal;

int	heredoc_create(t_data *minishell, char *limiter)
{
	char	*limiter_tmp;
	int		std_in;
	int		std_inb;

	limiter_tmp = NULL;
	if (init_dup_hd(&std_in, &std_inb) == KO || init_hd_fd_n_limiter(minishell,
			&limiter_tmp, limiter) == KO)
		return (KO);
	while (1)
	{
		if (heredoc_handler(minishell, std_in, std_inb, limiter_tmp) == KO)
			return(KO) ;
	}
	return(OK);
}

/*
le here_doc correspond au file <<
le limiter est lelement apres le << , lorsquil est appelé,
	ca met fin au here_doc
*/

int	heredoc_handler(t_data *minishell, int std_in, int std_inb,
		char *limiter_tmp)
{
	char	*line;

	line = NULL;
	g_signal = IN_HD;
	line = readline(HERE_DOC_MSG);
	if (dup_db_hd(std_in, std_inb, minishell) == KO)
		return (KO);
	if (g_signal == HD_STOP)
		if (handle_no_line_hd(minishell, limiter_tmp, std_in, std_inb) == KO)
			return (KO);
	if (line[0] && heredoc_next(line, limiter_tmp, minishell->fd_hd) == OK)
	{
		close_one_fd(std_in);
		if (dup2(std_inb, STDIN_FILENO) < 0)
		{
			close_one_fd(std_inb);
			return (perror(DUP_ERR), KO);
		}
		close_one_fd(std_inb);
		return (KO);
	}
	ft_putstr_fd(line, minishell->fd_hd);
	ft_putstr_fd("\n", minishell->fd_hd);
	free_n_set_var_null(&line);
	return (OK);
}

int	heredoc_next(char *line, char *limiter_tmp, int fd_heredoc)
{
	if (ft_strncmp(line, limiter_tmp, ft_strlen(line)) == 0)
	{
		close_one_fd(STDIN_FILENO);
		close_one_fd(fd_heredoc);
		free_n_set_var_null(&limiter_tmp);
		free_n_set_var_null(&line);
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
