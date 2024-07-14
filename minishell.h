/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:00:44 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/14 23:20:09 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* peut etre des includes en trop :) */

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

# define KO -1
# define OK 0
# define BUFF_OVERFLOW 2
# define BSIZE 4096

# define N_QUOTE 0
# define S_QUOTE 1
# define D_QUOTE 2

# define EXIT_JSP -1

# define HANDLE_ERROR "Minishell Error Code :"

/* prcess */
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
# define STRJOIN_ERR "Minishell Error : Malloc problem with strjoin\n"
# define STRDUP_ERR "Minishell Error : Malloc problem with strdup\n"

/* code d'erreur ?
	1 pour les erreurs de syntaxe,
	2 pour les erreurs de commandes
	3 pour les erreurs de fichiers, etc...

	BAD LONG...................ou pas :)
*/
typedef struct s_minishell	t_data;
typedef struct s_element	t_token;
typedef struct s_builtin	t_builtin;

/* structure pour gerer l'historique des commandes */

typedef struct s_minishell
{
	t_list					*token;
	t_list					*history;
	t_list					*actual_history;
	t_builtin				*builtins;

	char					**path;
	int						last_status;
}							t_data;

typedef struct s_element
{
	int						index;
	char					*str;
}							t_token;

typedef struct s_builtin
{
	char					**env;
	char					*pwd;
}							t_builtin;

int							init_minishell(t_data **minishell);
/* initiate */
int							get_env(t_data *minishell, char **env);
int							no_environment(t_data *minishell);
int							load_env(t_data *minishell, char **env);
int							load_path(t_data *minishell, int flag);
char						*trim_end(char *path_env);

/* liste chainée */
void						display_history(t_data *minishell);
void						clear__history(t_data **minishell);
void						add_to_history(t_data **minishell, char *command);
void						add_element(t_list *token, char buffer[BSIZE]);
void						ft_lstclear_custom(t_list **lst,
								void (*del)(void *));
t_list						*ft_lstnew_custom(char buffer[BSIZE]);
/* Read and parse command */
void						prompt(t_list *token, t_data *minishell);
void						process_char(char **prompt_loop, t_list **token,
								char *buffer, int *i);
void						add_token(t_list **token, char buffer[BSIZE]);
void						trim_space(char buffer[BSIZE]);
void						handle_operator(char **prompt_loop, t_list **token,
								char buffer[BSIZE]);
int							tokenize(char *prompt, t_list **token);
int							handle_buffer_overflow(t_list **token);
int							check_operator(char *str);

/* Execution */
char						*find_path(char *cmd, char **path);
int							redirection_dup(int fd_in, int fd_out);
int							execve_one_cmd(t_data *minishell, char *cmd_path,
								int fd_dest);
int							get_status_process(t_data *minishell, int status);

void						close_one_fd(int fd);

/* Built-in commands */
int							is_builtin(char *command);
void						env_cmd(char **env);

void						execute_builtin(char **args);
void						builtin_echo(char **args);
void						builtin_cd(char **args);
void						builtin_pwd(char **args);
void						builtin_env(char **args);
void						builtin_exit(char **args);
void						builtin_export(char **args);
void						builtin_unsetenv(char **args);

/* Signal handling */
void						handle_signals(void);
void						handle_sigquit(int sig);
void						handle_sigint(int sig);

/* Prout */
void						display_prompt(void);
void						display_intro(void);
void						print_token(void *content);
void						print_error(const char *msg);

/* memory */
void						*ft_realloc(void *ptr, size_t size);

/* str */
char						*cpy_twin(char **src, char buffer[BSIZE]);
void						handle_quote(char **prompt_loop, t_list **token,
								char buffer[BSIZE]);
/* check */
int							check_args(int argc, char **argv);
int							ft_strcmp(const char *s1, const char *s2);
int							have_twin(char *prompt);

char						*get_prompt(t_data **minishell);
char						*dollar_expansion(char *var, int quote_type,
								t_data *minishell);

/* Auto destruction minishell*/
void						apocalypse(t_data *minishell);
void						free_args(char **args);
void						free_commands(char ***commands);
void						free_double_char(char **array);
void						error_exit(const char *msg);
void						handle_error(int error_code, char *prompt);
void						handle_exit(t_data *minishell, char *prompt,
								t_list *token);
void						free_token(void *token);

/* Pas mal le franglish hein :) ?
	jadore tkt :D
*/
#endif
