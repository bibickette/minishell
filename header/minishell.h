/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yantoine <yantoine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:00:44 by yantoine          #+#    #+#             */
/*   Updated: 2024/06/20 16:56:13 by yantoine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

/*minishell/
├── Makefile
├── minishell.c
├── minishell.h
├── command.c
├── builtin.c
├── signal.c
├── utils.c
└── README.md
*/

/* Prompt (exemple: "minishell>> 'commands'") */
void	display_prompt(void);

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
void	builtin_cd(char **args);
void	builtin_pwd(char **args);
void	builtin_exit(char **args);
void	builtin_env(char **args);
void	builtin_export(char **args);
void	builtin_unsetenv(char **args);

/* Signal handling */
void	handle_signals(void);

/* Utilities */
void	free_args(char **args);
void	free_commands(char ***commands);
void	error_exit(const char *msg);

#endif
