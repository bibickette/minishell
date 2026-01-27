/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: phwang <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 16:00:44 by yantoine          #+#    #+#             */
/*   Updated: 2024/09/29 22:39:04 by phwang           ###   ########.fr       */
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

int				the_parser_set(t_list *token, t_data *minishell, char *prompt);
void			the_preparation(t_list *token, t_data *minishell);
void			the_execution(t_list *token, t_data *minishell);

/* initiate, get env */
int				init_minishell(t_data **minishell);
int				get_env(t_data *minishell, char **env);
int				no_environment(t_data *minishell);
int				handle_shell_level(t_data *minishell);
int				load_env(t_data *minishell, char **env);
int				load_right_split(t_data *minishell, int flag,
					char *path_from_env, char *path_env);
int				load_export_tab(t_data *minishell, char **env);
int				load_export_w_quote(char **export);
int				load_value_n_key_export(char **key_export, char **value_export,
					char **export);
int				load_path_from_flag(t_data *minishell, int flag,
					char **path_from_env, char *path_env);
int				load_path(t_data *minishell, int flag, char *path_env);
int				load_value(t_data *minishell, char *var, char **to_value,
					char *cmd_export);
int				is_valgrind_env(char **env);
char			*trim_end(char *path_env);

/* prompt */
void			display_intro(void);
void			print_token(void *content);
void			print_cmd(void *content);
void			print_double_tab(char **tab);

/* Read and parse command */
void			prompt(t_list *token, t_data *minishell);
void			get_prompt(t_data **minishell);
void			ft_lstclear_custom(t_list **lst, void (*del)(void *));
t_list			*ft_lstnew_custom(char buffer[BSIZE]);
void			ft_lstclear_custom_cmd(t_list **lst, void (*del)(void *));
void			ft_lstclear_custom_bis(t_list *head);
void			exit_cmd(t_list *token, t_cmd *cmd, t_data *minishell);
int				is_return_value(char *str);
long long int	set_exit_arg(long long int status);
int				is_smaller_than_longmin(char *str);

/* tokenization */
int				process_char(char **prompt_loop, t_list **token, char *buffer,
					int *i);
void			make_theim_increment(char **prompt_loop, char *buffer, int *i);
int				tokenize(char *prompt, t_list **token);
void			add_token(t_list **token, char buffer[BSIZE]);
void			trim_space(char buffer[BSIZE]);
void			handle_operator(char **prompt_loop, t_list **token,
					char buffer[BSIZE]);
int				handle_buffer_overflow(t_list **token);
int				check_operator(char *str);

/* Command tab */
int				init_cmd_list(t_data *minishell, t_list *token);
int				set_node(t_list *tmp, t_data *minishell, int *i);
int				add_t_cmd_back(t_data *minishell, int index);
int				fill_cmd_list(t_data *minishell, t_list *tmp);
int				fill_cmd_node(t_list *tmp, t_list *tmp_cmd_list);
int				fill_cmd_files_list(t_data *minishell, t_list *tmp);
int				init_files(t_list *cmd_list);
int				set_file(t_list *cmd_list, t_list *tmp, int *i);

int				is_not_hd(t_list *tmp);

/* put args stucked together */
int				join_token_if_needed(t_list *token, char *prompt,
					t_list *brut_list, char **t_pt);
int				join_token(t_list *token, int token_nb);
int				dupplicate_list(t_list *token, t_list **brut_list);
int				set_quote_n_put_back(t_list *token, t_list *brut_list);
int				put_quote_back(char **str, char quote);
int				increment_lists(t_list **brut_list);
int				check_new_prompt(char *new_prompt, char *tmp_brut);
int				join_token_in_lists(t_list *token, t_list *brut_list,
					t_list **tmp_brut);
int				load_new_prompt(char **new_prompt, char **tmp_prompt,
					char *token_str);
int				line_economy(char *new_prompt, char *tmp_brut);
int				start_join_token_if_needed(t_list *token, char *prompt,
					t_list *brut_list);
void			stick_next_token(t_list *is_next_token, t_list **tmp_head,
					t_list **next_tmp);

void			set_index_again(t_list *token, t_list *brut_list);

/* separate token if needed */
int				has_space(char *str);
int				separate_if_needed(t_data *minishell, t_list *token);
int				separate_token(t_list *to_separate, t_list *after);
void			put_separate_list_in_token(t_list *new_list,
					t_list *to_separate);

/* type of token */
void			set_type_operator(t_token *last_token);
void			set_token_type(t_list *head);
void			analyze_type(t_token *current, t_token *before);
void			put_redir_type(t_token *current, t_token *before);
void			current_is_word(t_token *current, t_token *before);
void			set_builtin_type(t_token *current);
void			reset_operator_type(t_token *current);
void			reset_cmd_pipe(t_list *head);
void			reset_cmd_pipe_type(t_list *current, int *cmd_on_pipe,
					int *on_pipe_nb);
void			reset_every_first_cmd(t_list *tmp);
int				is_cd(t_list *tmp);
int				is_echo_flag(char *str);

int				check_token_operator_order(t_list *token, t_data *minishell);
int				check_builtin(t_list *token);
int				check_every_condition(t_list *tmp);
int				check_builtin_condition(t_list *tmp);
int				check_every_builtin_n_type(t_list *token);

int				lf_spechar_list(t_data *minishell, t_list *token);
int				lf_n_quote(t_list *tmp, int *is_echo);
int				check_special_char(char *prompt);
int				check_more_special_char(char c);

/* dollar expansion */
char			*dollar_expansion(char *var, int quote_type, t_data *minishell);
char			*create_expansion_dollar(t_data *minishell, char *var,
					char *expanded, int quote_type);
char			*expansion_no_surround(char *var, t_data *minishell);
char			*keep_next_of_var(char **var);

/* expand dollar  everything */
int				expand_everything(t_data *minishell, t_list *token);
int				trim_token(t_list *tmp_head);
int				right_condition_for_expand(t_list *tmp_head,
					char *str_token_before);
int				start_expanding(t_data *minishell, char ***dollar_tab,
					char **str);
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
int				do_the_expansion(t_data *minishell, char **dollar_tab);
int				build_expand_n_replace(char **str_expanded,
					char ***expanded_exported, char **str);
int				has_dollar(char *var);
int				has_multiple_dollar(char *var);

/* history */
void			display_history(t_data *minishell);
void			clear__history(t_data **minishell);
void			add_to_history(t_data **minishell, char *command);

/**********************************************/

/*************************************/
/*        Execution functions        */
/*************************************/

/* redirection, file */
int				heredoc_create(t_data *minishell, char *limiter);
int				here_doc_create_all(t_data *minishell);
int				heredoc_next(char *line, char *limiter_tmp, int fd_heredoc);
int				init_dup_hd(int *std_in, int *std_inb);
int				dup_db_hd(int to_dup, int std_inb, t_data *minishell);
int				handle_no_line_hd(t_data *minishell, int std_in, int std_inb);
int				heredoc_handler(t_data *minishell, int std_in, int std_inb,
					char *limiter_tmp);
void			retrieve_norm(t_data *minishell);

int				take_all_hd_files(t_data *minishell, t_list *token);
int				count_n_allocate_files(t_data *minishell, t_list *token);
void			load_files_type(t_data *minishell, t_list *token);
int				char_add_back_tab(char ***original_tab, char *to_add);
int				count_n_copy_original_tab(char ***original_tab, char ***new_tab,
					int *nb_tab);
int				no_original_tab(char ***original_tab, char *to_add,
					char ***new_tab);
int				open_infile_type(t_file *file);
int				open_infile_hd_type(t_file *file);
int				open_outfile_type(t_file *file);
int				open_all_infile(t_data *minishell, t_cmd *cmd);
int				open_all_hd_file(t_data *minishell, t_cmd *cmd);
int				open_all_outfile(t_data *minishell, t_cmd *cmd);

int				file_type(t_list *tmp_head);
int				load_file_tab(t_data *minishell, char **dico_files);
int				has_infile(t_data *minishell, t_cmd *cmd);
int				has_outfile(t_cmd *cmd);
t_cmd			*get_cmd_by_index(t_data *minishell, int index);
int				open_infile(t_file *file);
int				open_outfile(t_file *file);
int				open_append_outfile(t_file *file);
void			close_all_files(t_file *files);
void			handle_file_hd(t_data *minishell);

/* Built-in commands */
int				export_all_arg(t_data *minishell, char **cmd_arg);
int				is_builtin(char *command);

/* built-in export*/
void			export_cmd_no_arg(char **export);
int				export_cmd_w_arg(char *var, t_data *minishell);
int				export_in_env(char *var, t_data *minishell);
int				replace_in_tab(char ***env_or_export, char *tmp_var,
					char **var);

int				export_in_export(char *var, char **key_export,
					t_data *minishell);
int				export_replacement_tab(char ***env_or_export, char **var);
int				load_right_export(char *var, char **key_export);
int				load_export_w_equal(char *var, char **key_export);

int				the_big_condition(char ***env_or_export, char *tmp_var, int i);

int				check_export_format(char *var, t_data *minishell);
int				has_equal(char *var);

/* builtin pwd*/
void			pwd_cmd(t_builtin *builtins);
/* built-in env */
void			env_cmd(char **env);
/* built-in echo */
void			echo_cmd(char **cmd_arg, int fd_out);
/* built-in unset*/
void			unset_cmd(t_data *minishell, char *var);
/* built-in cd */
int				cd_cmd(char *path);

/* Execution */
char			*find_path(char *cmd, char **path);
char			*get_path(t_data *minishell, t_cmd *cmd);
int				redirection_in(t_data *minishell, t_file *files, t_cmd *cmd,
					int std_in);
int				redirection_out(t_cmd *cmd, t_file *files, int std_out);

int				execve_one_cmd(t_data *minish, t_list *token);
int				do_redir_builtin_one_cmd(t_data *minish, int out);
void			execve_error(t_data *minishell, char *path, t_list *token);
int				execve_error_free(t_data *minish, char *path, t_list *token);

void			handle_builtin(t_data *minish, t_list *token);
int				execve_builtin(t_data *minishell, t_cmd *cmd);
int				first_part_choose_builtin(t_data *minishell, t_cmd *cmd);
void			do_single_fork(t_data *minish, t_list *token, t_cmd *cmd,
					int *pid);
void			child_single_fork(t_data *minish, t_list *token, t_cmd *cmd);
int				get_status_process(t_data *minishell, int *status, pid_t pid);
void			close_one_fd(int fd);
char			*split_n_path(t_data *minishell, t_cmd *cmd, t_list *token);
int				has_path(char *cmd);
char			*extract_cmd(char *cmd_arg);
int				check_cmd_value(char *str);
void			put_back_in_term_n_close(t_data *minish, int out);

int				init_pipe(t_data *minishell);
int				open_pipe(t_data *minishell);
int				error_open_pipe(t_data *minishell, int i);
void			execve_pipe(t_data *minish, t_list *token);
void			child_process(t_data *minishell, t_list *token, t_cmd *cmd);
void			do_the_dup(t_data *minishell, t_list *token, t_cmd *cmd);
void			dup_first_cmd(t_data *minishell, t_list *token, t_cmd *cmd);
void			dup_last_cmd(t_data *minishell, t_list *token, t_cmd *cmd);
void			wait_all_get_status(t_data *minishell);
void			close_all_pipes(t_data *minishell);
void			free_pipe_pid(t_data *minishell);

/**********************************************/

/*************************************/
/*         Utility functions         */
/*************************************/

/* Signal handling */
void			handle_signals(t_data *minishell);
void			handle_sigint(int signum);
void			handle_sigquit(int signum);
void			sigint_utils(void);

/* memory */
void			*ft_realloc(void *ptr, size_t size);

/* str */
char			*cpy_twin(char **src, char buffer[BSIZE]);
int				handle_quote(char **prompt_loop, t_list **token,
					char buffer[BSIZE]);
void			handle_space(char **prompt_loop, t_list **token,
					char buffer[BSIZE]);
char			*ft_strnstr_minish(char *s1, char *s2, size_t len);

/* check */
void			check_args(int argc, char **argv);
int				check_quote_type(char **prompt_loop);
int				ft_strcmp(const char *s1, const char *s2);
int				have_twin(char *prompt);

/* Auto destruction minishell*/
void			apocalypse(t_data *minishell);
void			free_builtins(t_builtin *builtins);
void			free_lists(t_data *minishell);
void			free_double_char(char ***array);
void			handle_exit(t_data *minishell);

void			free_token(void *token);
void			free_files_tab(t_data *minishell, t_file *files);
void			free_files_tab_cmd(t_cmd *cmd, t_file *files);
void			free_set_null(char **var);

int				create_tab(char ***tab, char *str, int *index, int word_nb);
char			**split_w_space(char *s);
int				is_white_space(char c);
int				countwords_wsp(const char *str);

/* temporary */
void			print_all_files(t_file *files);
void			print_double_tab(char **tab);

/**********************************************/

#endif
