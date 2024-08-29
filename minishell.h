/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:00:44 by yantoine          #+#    #+#             */
/*   Updated: 2024/08/29 17:35:13 by phwang           ###   ########.fr       */
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
	int			pipe;
	char		*redirection;
}				t_command;

typedef struct s_minishell
{
	t_list		*token;
	t_list		*history;
	t_list		*actual_history;
	t_list		*command_list;
	t_builtin	*builtins;

	t_file		*files;
	int			nb_files;

	char		**path;
	char		**command;
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
void			ft_lstclear_custom_bis(t_list *head);

/* tokenization */
int				process_char(char **prompt_loop, t_list **token, char *buffer,
					int *i);
void			print_command(void *content);
void			make_theim_increment(char **prompt_loop, char *buffer, int *i);
int				tokenize(char *prompt, t_list **token);
void			add_token(t_list **token, char buffer[BSIZE]);
void			trim_space(char buffer[BSIZE]);
void			handle_operator(char **prompt_loop, t_list **token,
					char buffer[BSIZE]);
int				handle_buffer_overflow(t_list **token);
int				check_operator(char *str);
// int				check_special_char(char *prompt);

/* type of token */
void			set_type_operator(t_token *last_token);
void			set_token_type(t_list *head);
void			analyze_type(t_token *current, t_token *before);
void			put_redir_type(t_token *current, t_token *before);
void			current_is_word(t_token *current, t_token *before);

/* dollar expansion */
char			*dollar_expansion(char *var, int quote_type, t_data *minishell);
char			*create_expansion_dollar(t_data *minishell, char *var,
					char *expanded, int quote_type);
char			*expansion_no_surround(char *var, t_data *minishell);
char			*expansion_no_surround_list(char *var, t_data *minishell);

/* expand dollar  everything */
void			expand_everything(t_data *minishell, t_list *token);
int				start_expanding(t_data *minishell, char ***dollar_tab,
					t_list *tmp_head);
int				set_dollar_n_expand(t_data *minishell, char ***dollar_tab,
					char ***expanded_exported);
int				build_unique_dollar(t_data *minishell, char **dollar,
					char **expanded_exported);
int				handle_multiple_dollar(t_data *minishell, char ***dollar_tab,
					char **expanded_exported);
int				first_step_multiple_dollar(t_data *minishell,
					char ***dollar_tab, char **expanded_exported);
int				add_doll_first_tab(t_data *minishell, char ***dollar_tab);
int				add_doll_all_tab(t_data *minishell, char ***dollar_tab,
					char *expanded_exported);
int				do_the_expansion(t_data *minishel, char **dollar_tab);
int				build_expand_n_replace(char **str_expanded,
					char ***expanded_exported, t_list *tmp_head);

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
int				take_all_files(t_data *minishell, t_list *token);
int	count_n_allocate_files(t_data *minishell, t_list *token);
int load_files_type(t_data *minishell, t_list *token);
int	char_add_back_tab(char ***original_tab, char *to_add);
int	count_n_copy_original_tab(char ***original_tab, char ***new_tab, int *nb_tab);
int	no_original_tab(char ***original_tab, char *to_add, char ***new_tab);


/* Built-in commands */
int				is_builtin(char *command);
/* built-in export*/
int				export_cmd(t_list **export_head, char *var, t_data *minishell);
int				exporting(char **tmp, char *var, char **exported,
					t_data *minishell);
int				export_check(char **tmp, char *var);
int				export_no_quote(char **exported, char *var, char *tmp);
int				export_single_quote(char **exported, char *var, char *tmp);
int				export_double_quote(t_data *minishell, char **exported,
					char *tmp, char *var);
int				export_handle_dollar(t_data *minishell,
					char ***expanded_exported, char *tmp, char **exported);
int				export_dollar_in_str(t_data *minishell,
					char **expanded_exported, char *tmp, char **exported);
int				build_the_export(char **exported, char **expanded_exported,
					char *var, char *tmp);
int				export_replacement(t_data *minishell, t_list *export_head,
					char *var, char **exported);
int				export_replacement_list(t_list *export_head, char **exported,
					char *tmp_var);
int				free_export_malloc(char **expanded_exported, char *tmp,
					char *exported);
int				has_dollar(char *var);
int				has_multiple_dollar(char *var);
int				has_equal(char *var);
/* builtin pwd*/
void			pwd_cmd(t_builtin *builtins);
/* built-in env */
void			env_cmd(char **env, t_list *export);
void			env_cmd_check_export(t_list *export);
/* built-in echo */
int				echo_cmd(t_list *token, int fd_dest);
/* built-in unset*/
void			unset_cmd(t_builtin *builtins, char *var);
void			unset_cmd_check_export(t_builtin *builtins, char *var);

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

t_list			*command_listing(t_list *token);
void			process_options(t_list **actual, t_token **actual_content,
					t_command *content);
void			process_command(t_list **actual, t_token **actual_content,
					t_command *content);
char			**add_argument(char **args, char *new_arg, int *size);
char			**add_option(char **options, char *new_option, int *size);
void			increment_actual(t_list **actual, t_token **actual_content);

/* check */
int				check_lexical(t_list *token);
int				check_args(int argc, char **argv);
int				check_quote_type(char **prompt_loop);
int				ft_strcmp(const char *s1, const char *s2);
int				have_twin(char *prompt);

/* Auto destruction minishell*/
void			apocalypse(t_data *minishell);
void			free_builtins(t_builtin *builtins);
void			free_command_list(t_list *command_list);
void			free_command(t_command *command);
void			free_lists(t_data *minishell);
void			free_double_char(char **array);
void			error_exit(const char *msg);
void			handle_error(int error_code, char *prompt);
void			handle_exit(t_data *minishell, char *prompt, t_list *token);
void			free_token(void *token);
void free_files_tab(t_data *minishell, t_file *files);

#endif
