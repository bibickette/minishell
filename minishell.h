/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:00:44 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/11 21:22:09 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/**********************************************/

/*************************************/
/*            SUMMARY :              */
/*************************************/
/*										*/
/*      - Includes         				*/
/*      - Codes errors        			*/
/*      - Messages errors       		*/
/*      - Structures         			*/
/*      - Prompt functions           */
/*      - Execution functions      		*/
/*      - Utility functions          */
/*										*/
/*************************************/

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
/* 127 : exit status for command not found */
/* 126 : exit status for command found but not executable*/

# define KO -1
# define OK 0
# define BUFF_OVERFLOW 2
# define BSIZE 4096

/* quote type */
# define N_QUOTE 0
# define S_QUOTE 1
# define D_QUOTE 2

/* type des tokens */

/* word et cmd*/
# define NO_TYPE 0
# define WORD_TYPE 1
# define CMD_TYPE 2
# define BUILTIN_TYPE 3
# define OPT_CMD_TYPE 4 // -
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
# define ERR_PWD "Minishell Error : Pwd"

/* parsing error */
# define QUOTE_ERR "Minishell Error : Single quote\n"
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

typedef struct s_builtin
{
	char		**env;
	char		*pwd;
}				t_builtin;

typedef struct s_minishell
{
	t_list		*token;
	t_list		*history;
	t_list		*actual_history;
	t_builtin	*builtins;

	char		**path;
	int			last_status;
	int			here_doc;
}				t_data;

/**********************************************/

/*************************************/
/*         Prompt functions          */
/*************************************/

/* initiate, get env */
int				init_minishell(t_data **minishell);
int				get_env(t_data *minishell, char **env);
int				no_environment(t_data *minishell);
int				load_env(t_data *minishell, char **env);
int				load_path(t_data *minishell, int flag);
char			*trim_end(char *path_env);

/* prompt */
void			display_prompt(void);
void			display_intro(void);
void			print_token(void *content);

/* Read and parse command */
void			prompt(t_list *token, t_data *minishell);
char			*get_prompt(t_data **minishell);
void			ft_lstclear_custom(t_list **lst, void (*del)(void *));
t_list			*ft_lstnew_custom(char buffer[BSIZE]);

/* tokenization */
int				process_char(char **prompt_loop, t_list **token, char *buffer,
					int *i);
int				tokenize(char *prompt, t_list **token);
void			add_token(t_list **token, char buffer[BSIZE]);
void			trim_space(char buffer[BSIZE]);
void			handle_operator(char **prompt_loop, t_list **token,
					char buffer[BSIZE]);
int				handle_buffer_overflow(t_list **token);
int				check_operator(char *str);
int				check_special_char(char *prompt);

/* type of token */
void			set_type_operator(t_token *last_token);
void			set_token_type(t_list *head);
void			analyze_type(t_token *current, t_token *before);
void			put_redir_type(t_token *current, t_token *before);
void			current_is_word(t_token *current, t_token *before);

/* dollar expansion */
char			*dollar_expansion(char *var, int quote_type, t_data *minishell);
char			*expansion_no_surround(char *var, t_data *minishell);
char			*expansion_parentheses(char *var, t_data *minishell);

/* history */
void			display_history(t_data *minishell);
void			clear__history(t_data **minishell);
void			add_to_history(t_data **minishell, char *command);
void			add_element(t_list *token, char buffer[BSIZE]);

/**********************************************/

/*************************************/
/*        Execution functions        */
/*************************************/

/* redirection, file */
void			heredoc_create(t_data *minishell, char *limiter);
int				heredoc_next(char *line, char *limiter_tmp, int fd_heredoc);

/* Built-in commands */
int				is_builtin(char *command);
void			env_cmd(char **env);
void			pwd_cmd(t_builtin *builtins);

/* Execution */
char			*find_path(char *cmd, char **path);
int				redirection_dup(int fd_in, int fd_out);
int				execve_one_cmd(t_data *minishell, char *cmd_path, int fd_dest);
void			execve_error(t_data *minishell, char *path, char **arg,
					int fd_dest);
int				get_status_process(t_data *minishell, int status, pid_t pid,
					int fd_dest);
void			close_one_fd(int fd);
void			split_n_path(t_data *minishell, char *cmd_arg, char ***arg,
					char **path);
/**********************************************/

/*************************************/
/*         Utility functions         */
/*************************************/

/* Signal handling */
void			handle_signals(void);
void			handle_sigquit(int sig);
void			handle_sigint(int sig);

/* memory */
void			*ft_realloc(void *ptr, size_t size);

/* str */
char			*cpy_twin(char **src, char buffer[BSIZE]);
int				handle_quote(char **prompt_loop, t_list **token,
					char buffer[BSIZE]);
void			handle_space(char **prompt_loop, t_list **token,
					char buffer[BSIZE]);

/* check */
int				check_args(int argc, char **argv);
int				check_quote_type(char **prompt_loop);
int				ft_strcmp(const char *s1, const char *s2);
int				have_twin(char *prompt);

/* Auto destruction minishell*/
void			apocalypse(t_data *minishell);
void			free_builtins(t_builtin *builtins);
void			free_lists(t_data *minishell);
void			free_double_char(char **array);
void			error_exit(const char *msg);
void			handle_error(int error_code, char *prompt);
void			handle_exit(t_data *minishell, char *prompt, t_list *token);
void			free_token(void *token);

#endif
