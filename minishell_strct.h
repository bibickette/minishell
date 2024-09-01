/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_strct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/30 22:50:40 by phwang            #+#    #+#             */
/*   Updated: 2024/09/01 23:13:52 by phwang           ###   ########.fr       */
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

# include "LIBFT/libft.h"
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
# define BUFF_OVERFLOW 2
# define BSIZE 4096

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
# define ARG_TYPE 99
# define BUILTIN_TYPE 3
# define OPT_TYPE 4 // -
/* redirection */
# define INFILE_TYPE 5
# define OUTFILE_TYPE 6
# define IN_REDIR_TYPE 7  // <
# define OUT_REDIR_TYPE 8 // >
/* heredoc */
# define HERE_DOC_TYPE 9    // <<
# define HD_LIMITER_TYPE 10 // EOF
# define HD_APPEND_TYPE 11  // >>
# define APPEND_FILE_TYPE 15
/* other */
# define PIPE_TYPE 12   // |
# define DOLLAR_TYPE 13 // $
# define EXECUTABLE_TYPE 14

/**********************************************/

/*************************************/
/*          Messages errors          */
/*************************************/

# define HANDLE_ERROR "Minishell Error Code :"

/* builtins error */
# define PWD_ERR "Minishell Error : Pwd"
# define EXPORT_ERR "Minishell Error : Export : Wrong Format\n"
# define EXPORT_MALLOC_ERR "Minishell Error : Malloc in builtin Export\n"
# define DOLLAR_EXPANSION_ERR "Minishell Error : Malloc in function Dollar Expansion\n"
# define EXPAND_MALLOC_ERR "Minishell Error : Malloc in function Expand Everything\n"

/* parsing error */
# define QUOTE_ERR "Minishell Error : Free quote\n"
# define SPECIAL_CHAR_ERR "Minishell Error : Special character\n"
# define BUFFER_ERR "Minishell Error : Buffer overflow\n"

/* process */
# define STATUS_ERR "A process hasn't ended well\n"
# define FORK_ERR "Minishell Error : Fork"
# define DUP_ERR "Minishell Error : Dup2"
# define EXECVE_ERR "Minishell Error : Execve"
# define CMD_NOT_FOUND "Minishell Error : Command not found\n"

/* environment errors */
# define ROOT_ENV "/etc/environment"
# define ERR_PATH "Minishell Error : Couldn't get the path\n"
# define ERR_ENV "Minishell Error : Couldn't get the environment\n"

/* malloc errors */
# define MALLOC_ERR "Minishell Error : Malloc\n"
# define SPLIT_ERR "Minishell Error : Malloc Split\n"
# define STRJOIN_ERR "Minishell Error : Malloc Strjoin\n"
# define STRDUP_ERR "Minishell Error : Malloc Strdup\n"
# define LSTNEW_ERR "Minishell Error : Malloc Lstnew\n"

/* file errors */
# define HERE_DOC_MSG "heredoc>"
# define HERE_DOC ".here_doc"
# define HERE_DOC_ERR "\nMinishell Error : Here-Document hasn't ended well\n"
# define INFILE_ERROR_FD "Couldn't open the infile\n"

/**********************************************/

/*************************************/
/*             Structures            */
/*************************************/
typedef struct s_element
{
	int			index;

	char		*str;
	int			type;
	int			quote;

}				t_token;

typedef struct s_file
{
	char		*name;
	int			fd;
	int			type;
}				t_file;

typedef struct s_builtin
{
	char		**env;
	char		*pwd;
	t_list		*export;

}				t_builtin;

typedef struct s_command
{
	char		*command;
	char		**option;
	char		**arg;
	char		*output;
	char		*input;
	int			pipe;
	char		*redirection;
}				t_command;

typedef struct s_minishell
{
	t_list		*history;
	t_list		*actual_history;
	t_list		*command_list;
	char		**command;

	t_list		*token;
	t_list		*brut_list;

	t_builtin	*builtins;

	t_file		*files;
	int			nb_files;

	char		**path;
	int			last_status;
	int			here_doc;
}				t_data;

/**********************************************/

#endif
