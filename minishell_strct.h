/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_strct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <phwang@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:50:40 by phwang            #+#    #+#             */
/*   Updated: 2026/01/27 18:11:24 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRCT_H
# define MINISHELL_STRCT_H

/**********************************************/

/************************************/
/*            SUMMARY :             */
/************************************/
/*									*/
/*      - Includes         			*/
/*      - Codes errors        		*/
/*      - Messages errors       	*/
/*      - Structures         		*/
/*									*/
/************************************/

/**********************************************/

/*************************************/
/*             Includes              */
/*************************************/

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

/**********************************************/

/*************************************/
/*            Codes errors           */
/*************************************/
/* 126 : exit status for command not found*/
/* 127 : exit status for command found but not executable */

# define KO -1
# define OK 0
# define M_KO 1
# define BUFF_OVERFLOW 2
# define BSIZE 4096

# define READ 0
# define WRITE 1

/* signals */
# define CTRL_D 9995
# define IN_PARENT 9996
# define WAS_IN_HD 9997
# define HD_STOP 9998
# define IN_HD 9999

/* quote type */
# define N_QUOTE 0
# define S_QUOTE 1
# define D_QUOTE 2
# define JOINED 3

/* type des tokens */

/* word et cmd*/
# define NO_TYPE 0
# define WORD_TYPE 1
# define CMD_TYPE 2
# define ARG_TYPE 3
# define BUILTIN_TYPE 4
# define OPT_TYPE 5 // -
/* redirection */
# define INFILE_TYPE 6
# define OUTFILE_TYPE 7
# define IN_REDIR_TYPE 8  // <
# define OUT_REDIR_TYPE 9 // >
/* heredoc */
# define HERE_DOC_TYPE 10   // <<
# define HD_LIMITER_TYPE 11 // EOF
# define HD_APPEND_TYPE 12  // >>
# define APPEND_FILE_TYPE 13
/* other */
# define PIPE_TYPE 14 // |

# define BUILT_NO_OPTION 16
# define BUILT_W_OPT 17
# define BUILT_NO_OPT_ARG 18

/**********************************************/

/*************************************/
/*          Messages errors          */
/*************************************/

# define HANDLE_ERROR "Minishell Error Code :"
# define STRNSTR_ERR "Minishell Error : Can't find anything in ft_strnstr\n"
# define ISATTY_ERR "Minishell Error : Can't redirect the minishell"
/* builtins error */
# define PWD_ERR "Minishell Error - PWD"
# define EXPORT_ERR "Minishell Error - EXPORT : Wrong Format\n"
# define EXPORT_MALLOC_ERR "Minishell Error : Malloc in builtin Export\n"
# define DOLLAR_EXPANSION_ERR "Minishell Error : \
Malloc in function Dollar Expansion\n"
# define EXPAND_MALLOC_ERR "Minishell Error : \
Malloc in function Expand Everything\n"
# define NOT_ENOUGH_ARG "Minishell Error - UNSET : Not enough arguments\n"
# define ECHO_ERR "Minishell Error - ECHO : Invalid option\n"
# define TOO_MANY_ARG "Minishell Error : Too many arguments\n"
# define EXIT_ERR "Minishell Error - EXIT : Need numerical argument\n"

/* parsing error */
# define QUOTE_ERR "Minishell Error : Free quote\n"
# define SPECIAL_CHAR_ERR "Minishell Error : Special character unquoted\n"
# define BUFFER_ERR "Minishell Error : Buffer overflow\n"
# define SYNTAX_ERR "Minishell Error : Syntax error\n"
# define BUILTIN_SYNTAX_ERR "Minishell Error : \
Builtin doesn't accept option/argument\n"

/* process */
# define STATUS_ERR "A process hasn't ended well\n"
# define PIPE_ERR "Minishell Error : Pipe"
# define FORK_ERR "Minishell Error : Fork"
# define DUP_ERR "Minishell Error : Dup2"
# define DUP_SIMPLE_ERR "Minishell Error : Dup"
# define EXECVE_ERR "Minishell Error : Execve"
# define CMD_NOT_FOUND "Minishell Error : Command not found : "
# define CLOSE_ERR "Minishell Error : Close"
# define UNLINK_ERR "Minishell Error : Unlink"

/* environment errors */
# define ROOT_ENV "/etc/environment"
# define ERR_PATH "Minishell Error : Couldn't get the path\n"
# define ERR_ENV "Minishell Error : Couldn't get the environment\n"
# define ERR_SHLVL "Minishell Error : Couldn't get the shell level\n"

/* malloc errors */
# define MALLOC_ERR "Minishell Error : Malloc\n"
# define SPLIT_ERR "Minishell Error : Malloc Split\n"
# define STRJOIN_ERR "Minishell Error : Malloc Strjoin\n"
# define STRDUP_ERR "Minishell Error : Malloc Strdup\n"
# define LSTNEW_ERR "Minishell Error : Malloc Lstnew\n"
# define ADD_BACK_TAB_ERR "Minishell Error : \
Malloc in function char_add_back_tab\n"

/* file errors */
# define HERE_DOC_MSG "heredoc> "
# define HERE_DOC ".here_doc"
# define HERE_DOC_ERR "Minishell Error : Here-Document hasn't ended well\n"
# define INFILE_ERROR_FD "Minishell Error : Couldn't open the infile\n"
# define OUTFILE_ERROR_FD "Minishell Error : Couldn't open the outfile\n"
# define FILE_ERR "Minishell Error : Access"
# define FILE_NOT_EXIST "No such file or directory\n"

/**********************************************/

/*************************************/
/*             Structures            */
/*************************************/

typedef struct s_element
{
	int			index;

	char		*str;
	int			type;
	int			builtin_type;
	int			quote;

}				t_token;

typedef struct s_file
{
	int			index;
	int			index_cmd;
	char		*name;

	int			type;
	int			fd;
	int			is_open;
}				t_file;

typedef struct s_builtin
{
	char		**env;
	char		*pwd;
	char		**export;
}				t_builtin;

typedef struct s_command
{
	int			index;
	int			cmd_type;

	char		*cmd;
	char		**cmd_args;

	int			nb_files;
	t_file		*files;

}				t_cmd;

typedef struct s_minishell
{
	char		*prompt;
	t_list		*token;
	t_list		*brut_list;

	t_builtin	*builtins;

	t_list		*history;
	t_list		*actual_history;

	t_file		*files;
	int			nb_hd_files;

	t_list		*list_cmd;
	int			**pipe_fd;
	int			*pid_tab;
	int			nb_cmd;

	char		**path;
	int			last_status;
	int			here_doc;

	int			fd_hd;

}				t_data;

/**********************************************/

#endif
