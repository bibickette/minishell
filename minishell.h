/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:00:44 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/30 18:35:33 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* peut etre des includes en trop :) */

# include "LIBFT/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <wait.h>
# include <stddef.h>
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
void	prompt(void);

/* Execution */

/* Built-in commands */
int		is_builtin(char *command);
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
void	display_intro(void);
void	display_prompt(void);
void	print_error(const char *msg);

/* Longueur :) */
/* libft :D */

/* str */
char	*command_join(char *commands, char *splited_prompt_char);
/* check */
int		check_args(int argc, char **argv);
int		ft_strcmp(const char *s1, const char *s2);

/* get */
char	*get_prompt(void);

/* Auto destruction minishell*/
void	apocalypse(void);
void	free_args(char **args);
void	free_commands(char ***commands);
void	free_double_char(char **array);
void	error_exit(const char *msg);

/* Pas mal le franglish hein :) ?
	jadore tkt :D
*/
#endif
