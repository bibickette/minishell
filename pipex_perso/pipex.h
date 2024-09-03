/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:00:19 by phwang            #+#    #+#             */
/*   Updated: 2024/06/12 19:19:03 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "LIBFT/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <sys/wait.h>

# define READ 0
# define WRITE 1

# define OK 1
# define NO 0
# define ERROR -1

# define PATH "PATH="
# define ARGC_ERR "Wrong number of argument\n"
# define ENV_ERROR "Problem with env\n"
# define PATH_ERROR "Path couldn't be found\n"
# define MALLOC_ERROR "Malloc failed, end of prog.\n"

# define DUP_ERROR "DUP2 ERROR\n"
# define PIPE_ERROR "PIPE ERROR\n"

# define OUTFILE_ERROR_FD "Couldn't open the outfile\n"
# define INFILE_ERROR "No such file or directory\n"
# define INFILE_ERROR_FD "Couldn't open the infile\n"

# define HERE_DOC_MSG "pipe heredoc>"
# define HERE_DOC ".here_doc"

# define PERR_MSG "Error"
# define CMD_ERROR "Command not found : "

typedef struct s_pipex
{
	int		fd_in;
	int		fd_out;

	int		empty_env;
	int		here_doc;

	char	**path;
	char	**cmds;
	char	**cmds_path;

	int		nb_cmds;
	int		**pipe_tab;

	pid_t	*pid_tab;

}			t_pipex;

int			get_env_path(int argc, char **argv, char **env, t_pipex *pipex);
void		set_null_struct(t_pipex *pipex);
int			get_cmds(int argc, char **argv, t_pipex *pipex);
void		check_outfile(char *fd_out, t_pipex *pipex);
void		check_infile(char *fd_in, t_pipex *pipex);

int			check_absolute_path(char **argv, int argc, t_pipex *pipex);

void		exit_error(t_pipex *pipex, char *error_msg);
void		tab_free(char **tab);
void		free_all(t_pipex *pipex);
int			return_err_msg(char *msg);

int			cmd_exist(t_pipex *pipex, char **path, char **cmds);
int			try_path(t_pipex *pipex, char **path, char **cmd_arg);
/*copie le path sur la cmd dans le cmd path tab*/
int			cpy_path_cmd(t_pipex *pipex, char *path_cmd, int cmd);
/*copies les cmd dans le cmd tab*/
int			create_cmd(t_pipex *pipex, int argc, char **argv);
/*malloc cmd size et met a null la derniere case*/
int			create_cmd_path(t_pipex *pipex);

/*check si il y a un / : signe dun path*/
int			has_path(char *cmd);
int			separate_path_cmd(t_pipex *pipex, char **cmd_arg, int cmd_nb);
char		*extract_cmd(char *cmd_arg);

int			test_path(t_pipex *pipex, char **path, char **cmd_arg, int cmd);
int			pid_pipe_tab_create(t_pipex *pipex);

void		do_pipex(t_pipex *pipex, char **env);

void		open_pipe(t_pipex *pipex);
void		child_process(t_pipex *pipex, char **env, int cmd);
void		pipex_dup(t_pipex *pipex, int in, int out);
int			execve_cmd(t_pipex *pipex, int cmd, char **env);
void		close_fds_pipes(t_pipex *pipex);

void		wait_child(t_pipex *pipex);

void		pipex_error(t_pipex *pipex);
int			ft_strcmp(char *s, char *s2);
void		heredoc_next(char *line, char *limiter, int fd_heredoc);

#endif