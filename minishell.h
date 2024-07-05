
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:00:44 by yantoine          #+#    #+#             */
/*   Updated: 2024/07/05 18:08:20 by yantoine         ###   ########.fr       */
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

# define KO 0
# define OK 1
# define BUFF_OVERFLOW 2
# define BSIZE 4096

/* code d'erreur ?
	1 pour les erreurs de syntaxe,
	2 pour les erreurs de commandes
	3 pour les erreurs de fichiers, etc...

	BAD LONG...................ou pas :)
*/

typedef struct s_element
{
	int					index;
	char				*str;
}	t_token;

/* liste chainée */
void	add_element(t_list *minishell, char buffer[BSIZE]);
void	ft_lstclear_custom(t_list **lst, void (*del)(void*));
t_list	*ft_lstnew_custom(char buffer[BSIZE]);
/* Read and parse command */
void	prompt(t_list *minishell);
int		tokenize(char *prompt, t_list **minishell);

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
void	print_token(void *content);
void	print_error(const char *msg);

/* memory */
void	*ft_realloc(void *ptr, size_t size);

/* str */
char		*cpy_twin(char *src, char buffer[BSIZE]);
void	handle_quote(char *prompt_loop, t_list **minishell, char buffer[BSIZE]);
/* check */
int		check_args(int argc, char **argv);
int		ft_strcmp(const char *s1, const char *s2);
int		have_twin(char *prompt);

/* get */
char	*get_prompt(void);

/* Auto destruction minishell*/
void	apocalypse(void);
void	free_args(char **args);
void	free_commands(char ***commands);
void	free_double_char(char **array);
void	error_exit(const char *msg);
void	handle_error(int error_code, char *prompt);
void	free_token(void *token);

/* Pas mal le franglish hein :) ?
	jadore tkt :D
*/
#endif
