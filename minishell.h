/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:00:44 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/03 18:44:06 by phwang           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/**********************************************/

/************************************/
/*            SUMMARY :             */
/************************************/
/*									*/
/*      - Include         			*/
/*      - Prompt functions          */
/*      - Execution functions      	*/
/*      - Utility functions         */
/*									*/
/************************************/

/**********************************************/

/*************************************/
/*             Includes              */
/*************************************/

# include "minishell_strct.h"

/*************************************/
/*         Prompt functions          */
/*************************************/

/* initiate, get env */
int		init_minishell(t_data **minishell);
int		get_env(t_data *minishell, char **env);
int		no_environment(t_data *minishell);
int		load_env(t_data *minishell, char **env);
int		load_path(t_data *minishell, int flag);
char	*trim_end(char *path_env);
int		load_original_export(char **env, t_list **real_export);

/* prompt */
void	display_prompt(void);
void	display_intro(void);
void	print_token(void *content);

/* Read and parse command */
void	prompt(t_list *token, t_data *minishell);
char	*get_prompt(t_data **minishell);
void	ft_lstclear_custom(t_list **lst, void (*del)(void *));
t_list	*ft_lstnew_custom(char buffer[BSIZE]);
void	ft_lstclear_custom_bis(t_list *head);

/* tokenization */
int		process_char(char **prompt_loop, t_list **token, char *buffer, int *i);
void	print_command(void *content);
void	make_theim_increment(char **prompt_loop, char *buffer, int *i);
int		tokenize(char *prompt, t_list **token);
int		go_next(t_list **actual, t_command **actual_command);
char	**set_command_list(t_list *token);
void	add_token(t_list **token, char buffer[BSIZE]);
void	trim_space(char buffer[BSIZE]);
void	handle_operator(char **prompt_loop, t_list **token, char buffer[BSIZE]);
int		handle_buffer_overflow(t_list **token);
int		check_operator(char *str);

/* put args stucked together */
int		join_token_if_needed(t_list *token, char *prompt, t_list *brut_list,
			char **t_pt);
int		join_token(t_list *token, t_list *is_next_token);
int		dupplicate_list(t_list *token, t_list **brut_list);
int		set_quote_n_put_back(t_list *token, t_list *brut_list);
int		put_quote_back(char **str, char quote);
int		increment_lists(t_list **token, t_list **brut_list);
int		check_new_prompt(char *new_prompt, char *tmp_brut);
int		join_token_in_lists(t_list *token, t_list *brut_list,
			t_list **tmp_token, t_list **tmp_brut);
int		load_new_prompt(char **new_prompt, char **tmp_prompt, char *token_str);
int		line_economy(char *new_prompt, char *tmp_brut);
int		start_join_token_if_needed(t_list *token, char *prompt,
			t_list *brut_list);
void	stick_next_token(t_list *is_next_token, t_list **tmp_head,
			t_list **next_tmp);
int		set_entire_command(t_list *command_list);
int		go_next(t_list **actual, t_command **actual_command);

/* type of token */
void	set_type_operator(t_token *last_token);
void	set_token_type(t_list *head);
void	analyze_type(t_token *current, t_token *before);
void	put_redir_type(t_token *current, t_token *before);
void	current_is_word(t_token *current, t_token *before);
int		check_token_operator_order(t_list *token, t_data *minishell);

int		lf_spechar_list(t_list *token);
int		check_special_char(char *prompt);
int check_token_special_char(t_list *token);

/* dollar expansion */
char	*dollar_expansion(char *var, int quote_type, t_data *minishell);
char	*create_expansion_dollar(t_data *minishell, char *var, char *expanded,
			int quote_type);
char	*expansion_no_surround(char *var, t_data *minishell);
char	*expansion_no_surround_list(char *var, t_data *minishell);

/* expand dollar  everything */
void	expand_everything(t_data *minishell, t_list *token);
int		start_expanding(t_data *minishell, char ***dollar_tab,
			t_list *tmp_head);
int		set_dollar_n_expand(t_data *minishell, char ***dollar_tab,
			char ***expanded_exported);
int		build_unique_dollar(t_data *minishell, char **dollar,
			char **expanded_exported);
int		handle_multiple_dollar(t_data *minishell, char ***dollar_tab,
			char **expanded_exported);
int		first_step_multiple_dollar(t_data *minishell, char ***dollar_tab,
			char **expanded_exported);
int		add_doll_first_tab(t_data *minishell, char ***dollar_tab);
int		add_doll_all_tab(t_data *minishell, char ***dollar_tab,
			char *expanded_exported);
int		do_the_expansion(t_data *minishel, char **dollar_tab);
int		build_expand_n_replace(char **str_expanded, char ***expanded_exported,
			t_list *tmp_head);
int		has_dollar(char *var);
int		has_multiple_dollar(char *var);

/* history */
void	display_history(t_data *minishell);
void	clear__history(t_data **minishell);
void	add_to_history(t_data **minishell, char *command);
void	add_element(t_list *token, char buffer[BSIZE]);

/**********************************************/

/*************************************/
/*        Execution functions        */
/*************************************/

/* redirection, file */
void	heredoc_create(t_data *minishell, char *limiter);
int		heredoc_next(char *line, char *limiter_tmp, int fd_heredoc);
int		take_all_files(t_data *minishell, t_list *token);
int		count_n_allocate_files(t_data *minishell, t_list *token);
int		load_files_type(t_data *minishell, t_list *token);
int		char_add_back_tab(char ***original_tab, char *to_add);
int		count_n_copy_original_tab(char ***original_tab, char ***new_tab,
			int *nb_tab);
int		no_original_tab(char ***original_tab, char *to_add, char ***new_tab);
int		open_file(t_data *minishell, t_file *file);
void	open_infile(t_file *file);
void	open_outfile(t_file *file);
void	open_append_outfile(t_file *file);
void	close_all_files(t_file *files);

/* Built-in commands */
int		is_builtin(char *command);
/* built-in export*/
int		export_cmd(t_list **export_head, char *var, t_data *minishell);
int		export_replacement(t_data *minishell, t_list *export_head, char **var);
int		export_replacement_list(t_list *export_head, char **var, char *tmp_var);
/* builtin pwd*/
void	pwd_cmd(t_builtin *builtins);
/* built-in env */
void	env_cmd(char **env, t_list *export);
void	env_cmd_check_export(t_list *export);
/* built-in echo */
int		echo_cmd(t_list *token, int fd_dest);
/* built-in unset*/
void	unset_cmd(t_builtin *builtins, char *var);
void	unset_cmd_check_export(t_builtin *builtins, char *var);

/* Execution */
int		get_fd(char *path);
char	*find_path(char *cmd, char **path);
int		redirection_dup(int fd_in, int fd_out);
int		execve_one_cmd(t_data *minishell, char *cmd_path, int fd_dest);
void	execve_error(t_data *minishell, char *path, char **arg, int fd_dest);
void	execution(t_data *minishell);
int		get_status_process(t_data *minishell, int status, pid_t pid,
			int fd_dest);
void	close_one_fd(int fd);
void	split_n_path(t_data *minishell, char *cmd_arg, char ***arg,
			char **path);
/**********************************************/

/*************************************/
/*         Utility functions         */
/*************************************/

/* Signal handling */
void	handle_signals(void);
void	handle_sigquit(int sig);
void	handle_sigint(int sig);

/* memory */
void	*ft_realloc(void *ptr, size_t size);

/* str */
char	*cpy_twin(char **src, char buffer[BSIZE]);
int		handle_quote(char **prompt_loop, t_list **token, char buffer[BSIZE]);
void	handle_space(char **prompt_loop, t_list **token, char buffer[BSIZE]);

t_list	*command_listing(t_list *token);
void	process_options(t_list **actual, t_token **actual_content,
			t_command *content);
void	process_command(t_list **actual, t_token **actual_content,
			t_command *content);
char	**add_argument(char **args, char *new_arg, int *size);
char	**add_option(char **options, char *new_option, int *size);
void	increment_actual(t_list **actual, t_token **actual_content);

/* check */
int		check_lexical(t_list *token);
int		check_args(int argc, char **argv);
int		check_quote_type(char **prompt_loop);
int		ft_strcmp(const char *s1, const char *s2);
int		have_twin(char *prompt);

/* Auto destruction minishell*/
void	apocalypse(t_data *minishell);
void	free_builtins(t_builtin *builtins);
void	free_command_list(t_list *command_list);
void	free_command(t_command *command);
void	free_lists(t_data *minishell);
void	free_double_char(char **array);
void	error_exit(const char *msg);
void	handle_error(int error_code, char *prompt);
void	handle_exit(t_data *minishell, char *prompt, t_list *token);
void	free_token(void *token);
void	free_files_tab(t_data *minishell, t_file *files);

/* temporary */
void	print_all_files(t_file *files);

/**********************************************/

#endif
