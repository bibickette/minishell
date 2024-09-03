# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phwang <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/24 17:06:00 by phwang            #+#    #+#              #
#    Updated: 2024/06/07 15:45:44 by phwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

SRC_DIR = src
OBJ_DIR = obj

LIBFT = -L./LIBFT -lft

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

SRC = \
	pipe_utils.c \
	pipe.c \
	free.c \
	cmds_create.c \
	cmds_check.c \
	cmds_extract.c \
	get_data.c
	
SRC_MAIN = \
	$(SRC) \
	main.c
	
SRC_BONUS = \
	$(SRC) \
	heredoc.c \
	main_bonus.c
	

OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC_MAIN)))))

OBJ_BONUS = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC_BONUS)))))

#PROGRESS BAR
TOTAL_SRCS := $(words $(SRC))
COMPILED_SRCS := 0
#COLOR SET
COLOR_RESET = \e[0m
COLOR_GREEN = \e[0;35m
COLOR_BLUE = \e[0;35m

.PHONY: all clean fclean re bonus rebonus

all: $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

	@$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
	@echo -n "$(COLOR_BLUE)Compiling Objects Pipex: $(COLOR_RESET)[$(COLOR_GREEN)"
	@for i in $(shell seq 1 25); do \
		if [ $$i -le $$(($(COMPILED_SRCS)*25/$(TOTAL_SRCS))) ]; then \
			echo -n "♣"; \
		else \
			echo -n "."; \
		fi; \
	done
	@echo -n "$(COLOR_RESET)] $(COMPILED_SRCS)\r"

$(NAME): $(OBJ_DIR) $(OBJ)
	@echo "$(COLOR_BLUE)\nCompiling Pipex...$(COLOR_RESET)"
	@make -s -C LIBFT
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "$(COLOR_GREEN)Pipex is ready to begin !$(COLOR_RESET)        "

clean:
	@make -s -C LIBFT clean
	@rm -rf $(OBJ_DIR)
	
fclean: clean
	@echo "$(COLOR_BLUE)✘✘✘ Deleting Pipex... ✘✘✘$(COLOR_RESET)"
	@make -s -C LIBFT fclean
	@rm -f $(NAME)
	@echo "$(COLOR_GREEN)✘✘✘ Pipex fcleaned ! ✘✘✘$(COLOR_RESET)        "

re:	fclean all

rebonus: fclean bonus

bonus: $(OBJ_DIR) $(OBJ_BONUS)
	@echo "$(COLOR_BLUE)\nCompiling Pipex Bonus...$(COLOR_RESET)"
	@make -s -C LIBFT
	@$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) -o $(NAME)
	@echo "$(COLOR_GREEN)Pipex Bonus is ready to begin !$(COLOR_RESET)        "
