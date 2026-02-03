# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phwang <phwang@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/20 22:44:43 by phwang            #+#    #+#              #
#    Updated: 2026/02/03 18:33:05 by phwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = -L./libft -lft

CC = cc

INCLUDE = -I. -I./libft
CFLAGS = -Wall -Wextra -Werror $(INCLUDE)

# Source directories
SRC_DIR = src
OBJ_DIR = obj

# Source files
BUILTINS_DIR = $(SRC_DIR)/builtins
DOLLAR_DIR = $(SRC_DIR)/dollar
EXECUTION_DIR = $(SRC_DIR)/execution
FILES_DIR = $(SRC_DIR)/files
FREE_DIR = $(SRC_DIR)/free
INITIATE_DIR = $(SRC_DIR)/initiate
PROMPT_DIR = $(SRC_DIR)/prompt
REDIRECTION_DIR = $(SRC_DIR)/redirection
REINITIATE_DIR = $(SRC_DIR)/reinitiate_tokens
TOKENIZE_DIR = $(SRC_DIR)/tokenize
UTILS_DIR = $(SRC_DIR)/utils

# List all source files manually
SRC = $(SRC_DIR)/main.c \
	  $(BUILTINS_DIR)/export_utils.c \
	  $(BUILTINS_DIR)/exit.c \
      $(BUILTINS_DIR)/cd.c \
      $(BUILTINS_DIR)/add_to_history.c \
      $(BUILTINS_DIR)/unset.c \
      $(BUILTINS_DIR)/pwd.c \
      $(BUILTINS_DIR)/export.c \
      $(BUILTINS_DIR)/export_no_arg.c \
      $(BUILTINS_DIR)/is_builtin.c \
      $(BUILTINS_DIR)/echo.c \
      $(BUILTINS_DIR)/display_history.c \
      $(BUILTINS_DIR)/env.c \
	  $(DOLLAR_DIR)/split_w_space.c \
      $(DOLLAR_DIR)/build_expansion.c \
      $(DOLLAR_DIR)/handle_multiple_dollar.c \
      $(DOLLAR_DIR)/dollar_expansion.c \
      $(DOLLAR_DIR)/expand_everything.c \
      $(EXECUTION_DIR)/dup_pipes.c \
      $(EXECUTION_DIR)/get_status_process.c \
      $(EXECUTION_DIR)/exec_pipe.c \
      $(EXECUTION_DIR)/exec_one_cmd_child.c \
      $(EXECUTION_DIR)/free_in_exec.c \
      $(EXECUTION_DIR)/init_pipes.c \
      $(EXECUTION_DIR)/find_path.c \
      $(EXECUTION_DIR)/exec_one_cmd.c \
      $(EXECUTION_DIR)/exec_builtin.c \
      $(EXECUTION_DIR)/cmd_list.c \
      $(FILES_DIR)/files_take_all.c \
      $(FILES_DIR)/files.c \
	  $(FILES_DIR)/files_utils.c \
      $(FILES_DIR)/here_doc_utils.c \
      $(FILES_DIR)/here_doc.c \
      $(FILES_DIR)/init_files.c \
      $(FREE_DIR)/ft_lstclear_custom.c \
      $(FREE_DIR)/apocalypse.c \
      $(FREE_DIR)/free_double_char.c \
      $(FREE_DIR)/free_token.c \
      $(FREE_DIR)/free_files.c \
      $(FREE_DIR)/clear_history.c \
      $(FREE_DIR)/ft_lst_new_custom.c \
      $(FREE_DIR)/free_command.c \
      $(INITIATE_DIR)/init_minishell.c \
	  $(INITIATE_DIR)/shlvl.c \
      $(INITIATE_DIR)/get_env.c \
	  $(INITIATE_DIR)/get_env_utils.c \
      $(INITIATE_DIR)/get_export.c \
      $(PROMPT_DIR)/check_args.c \
      $(PROMPT_DIR)/display_intro.c \
      $(PROMPT_DIR)/handle_sig.c \
      $(PROMPT_DIR)/get_prompt.c \
      $(PROMPT_DIR)/handle_exit.c \
      $(PROMPT_DIR)/prompt.c \
      $(REDIRECTION_DIR)/redirection.c \
      $(REDIRECTION_DIR)/open_files.c \
      $(REDIRECTION_DIR)/close_files.c \
      $(REINITIATE_DIR)/join_tokens_if_needed.c \
      $(REINITIATE_DIR)/check_token_order.c \
      $(REINITIATE_DIR)/check_special_char.c \
      $(REINITIATE_DIR)/set_token_type.c \
      $(REINITIATE_DIR)/join_tokens_needed_utils.c \
      $(REINITIATE_DIR)/join_tokens.c \
      $(REINITIATE_DIR)/set_toktype_precise.c \
      $(REINITIATE_DIR)/set_type_operator.c \
      $(REINITIATE_DIR)/utils.c \
      $(REINITIATE_DIR)/separate_if_needed.c \
      $(REINITIATE_DIR)/dupplicate_lists.c \
      $(REINITIATE_DIR)/ft_strnstr_minish.c \
      $(TOKENIZE_DIR)/tokenize.c \
      $(TOKENIZE_DIR)/process_char.c \
      $(TOKENIZE_DIR)/handle_buffer_overflow.c \
      $(TOKENIZE_DIR)/check_operator.c \
      $(TOKENIZE_DIR)/trim_space.c \
      $(TOKENIZE_DIR)/check_quote_type.c \
      $(TOKENIZE_DIR)/handle_operator.c \
      $(TOKENIZE_DIR)/handle_quote.c \
      $(TOKENIZE_DIR)/cpy_twin.c \
      $(TOKENIZE_DIR)/have_twin.c \
      $(TOKENIZE_DIR)/handle_space.c \
      $(TOKENIZE_DIR)/add_token.c \
      $(UTILS_DIR)/ft_realloc.c \
      $(UTILS_DIR)/print.c \
      $(UTILS_DIR)/double_tab_print.c \
      $(UTILS_DIR)/ft_strcmp.c


OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

#PROGRESS BAR
TOTAL_SRCS := $(words $(SRC))
COMPILED_SRCS := 0
#COLOR SET
COLOR_RESET = \e[0m
COLOR_GREEN = \e[0;35m
COLOR_BLUE = \e[0;35m

.PHONY: all clean fclean re

all: $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/builtins $(OBJ_DIR)/dollar $(OBJ_DIR)/execution $(OBJ_DIR)/files $(OBJ_DIR)/free $(OBJ_DIR)/initiate $(OBJ_DIR)/prompt $(OBJ_DIR)/redirection $(OBJ_DIR)/reinitiate_tokens $(OBJ_DIR)/tokenize $(OBJ_DIR)/utils
	@$(CC) $(CFLAGS) -o $@ -c $< 

	@$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
	@echo -n "$(COLOR_BLUE)Compiling Objects TinyShell: $(COLOR_RESET)[$(COLOR_GREEN)"
	@for i in $(shell seq 1 25); do \
		if [ $$i -le $$(($(COMPILED_SRCS)*25/$(TOTAL_SRCS))) ]; then \
			echo -n "♣"; \
		else \
			echo -n "."; \
		fi; \
	done
	@echo -n "$(COLOR_RESET)] $(COMPILED_SRCS)/$(TOTAL_SRCS)\r"

$(NAME) : $(OBJ_DIR) $(OBJ)
	@echo "$(COLOR_BLUE)\nCompiling TinyShell...$(COLOR_RESET)"
	@make -s -C libft
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME) 
	@echo "$(COLOR_GREEN)TinyShell Compilation complete !$(COLOR_RESET)        "

clean:
	@make -s -C libft clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "$(COLOR_BLUE)✘✘✘ Deleting TinyShell... ✘✘✘$(COLOR_RESET)"
	@make -s -C libft fclean
	@rm -f $(NAME)
	@echo "$(COLOR_GREEN)✘✘✘ TinyShell fcleaned ! ✘✘✘$(COLOR_RESET)        "

re: fclean all
