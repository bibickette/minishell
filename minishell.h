/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:00:44 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/20 21:21:33 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* peut etre des includes en trop :) */

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <wait.h>
# include <signal.h>
# include <errno.h>

/* code d'erreur ?
	1 pour les erreurs de syntaxe,
	2 pour les erreurs de commandes
	3 pour les erreurs de fichiers, etc...

	BAD LONG...................ou pas :)
*/


/* suggestion des dipositions des fichiers:

minishell/
└── README.md
├── Makefile
├── minishell.h
├── sources/
	├── minishell.c
	├── command.c
	├── builtin.c
	├── signal.c
	├── error.c
	└── etc...

   les noms des fichiers sont des suggestions,
	tu peux les renommer si tu veux c'est juste pour la forme
*/

/* Read and parse command */
char	*read_command(void);
char	**parse_command(char *command);

/* Execution */
void	execute_command(char **args);
void	execute_pipeline(char ***commands);
void	execute_redirection(char **args);

/* Built-in commands */
int		is_builtin(char **args);
void	execute_builtin(char **args);
void	builtin_echo(char **args);
void	builtin_cd(char **args);
void	builtin_pwd(char **args); // c kom si ct fait
void	builtin_env(char **args); // c kom si ct fait
void	builtin_exit(char **args);
void	builtin_export(char **args);
void	builtin_unsetenv(char **args);

/* Signal handling */
void	handle_signals(void);

/* Prout */
void	ft_putstr_fd(const char *str, int fd);
void	display_prompt(void);
void	print_error(const char *msg);

/* Longueur :) */
int		ft_strlen(const char *str);

/* Utilities */
void	free_args(char **args);
void	free_commands(char ***commands);
void	error_exit(const char *msg);


/* Pas mal le franglish hein :) ?
	il y aura peut etre tout en anglais sauf si ca ne te perturbe pas,
	je trouve juste que "fonction integre" et "lecture et analyse" sonne bizarement
*/
#endif
