/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:00:44 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/12 22:10:31 by phwang           ###   ########.fr       */
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

# define KO 0
# define OK 1
# define BUFF_OVERFLOW 2
# define BSIZE 4096

# define EXIT_JSP -1

# define FORK_ERR "Minishell Error : Fork\n"
# define STATUS_ERR "A process hasn't ended well\n"

# define HANDLE_ERROR "Minishell Error Code :"

/* environment errors */
# define ORIGINEL_ENV "/etc/environment"
# define ERR_PATH "Minishell Error : Couldn't get the path\n"
# define ERR_ENV "Minishell Error : Couldn't get the environment\n"
# define NO_PATH_ENV \
	"Minishell Error : Couldn't find any path for the env cmd\n"

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

typedef struct s_minishell
{
	t_list					*token;
	t_builtin				*builtins;

	char					**path;
	char					**env;
}							t_data;

typedef struct s_element
{
	int						index;
	char					*str;
}							t_token;

typedef struct s_builtin
{
	char					*pwd;
}							t_builtin;

int							init_minishell(t_data **minishell);
/* initiate */
int							get_env(t_data *minishell, char **env);
int							no_environment(t_data *minishell);
int							load_env(t_data *minishell, char **env);
int							load_path(t_data *minishell, int flag);
char						*trim_end(char *path_env);
int							execve_one_cmd(char *cmd_path, t_data *minishell,
								int fd_dest);

/* liste chainée */
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
void						display_intro(void);
void						display_prompt(void);
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

/* get */
char						*get_prompt(void);

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
