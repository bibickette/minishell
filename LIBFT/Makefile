# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phwang <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 13:04:16 by phwang            #+#    #+#              #
#    Updated: 2024/09/22 14:10:46 by phwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Name of my prog
NAME = libft.a
FT_PRINTF = ft_printf/libftprintf.a

#DIRECTORIES
SRC_DIR = src/*
OBJ_DIR = obj

#SRC FILES AND OBJECTS FILES, ALL FILES with the command : find . -name "ft_*.c"
SRC =  \
	countwords.c \
	strjoin_wfree.c \
	fibonacci.c \
	nb_is_prime.c \
	ft_itoa.c \
	ft_atoi.c \
	find_next_prime.c \
	nb_sqrt.c \
	power_nb.c \
	factorial.c \
	ft_memcpy.c \
	ft_memcmp.c \
	ft_memchr.c \
	ft_memmove.c \
	ft_memset.c \
	ft_lstiter_bonus.c \
	ft_lstadd_front_bonus.c \
	ft_lstnew_bonus.c \
	ft_lstdelone_bonus.c \
	ft_lstadd_back_bonus.c \
	ft_lstclear_bonus.c \
	ft_lstsize_bonus.c \
	ft_lstmap_bonus.c \
	ft_lstlast_bonus.c \
	pile_clear.c \
	pile_size.c \
	pile_addback.c \
	get_next_line_utils02.c \
	get_next_line_utils.c \
	get_next_line.c \
	ft_is_white_space \
	ft_isprint.c \
	ft_isdigit.c \
	ft_isascii.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_strrchr.c \
	ft_strjoin.c \
	ft_strlen.c \
	ft_tolower.c \
	ft_strdup.c \
	ft_split.c \
	ft_strlcpy.c \
	ft_strlcat.c \
	ft_strncmp.c \
	ft_substr.c \
	ft_strchr.c \
	ft_striteri.c \
	ft_toupper.c \
	ft_strtrim.c \
	ft_strmapi.c \
	ft_bzero.c \
	ft_strnstr.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c

OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

#PROGRESS BAR
TOTAL_SRCS := $(words $(SRC))
COMPILED_SRCS := 0
#COLOR SET
COLOR_RESET = \e[0m
COLOR_GREEN = \e[34m
COLOR_BLUE = \e[34m

#COMPILER & FLAGS
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

#Not a file
.PHONY: all clean fclean re 

#make start here
#compile the NAME then clean the OBJ
all: $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

#creer un dossier pour ranger les .o
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

	@$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
	@echo -n "$(COLOR_BLUE)Compiling Objects Libft: $(COLOR_RESET)[$(COLOR_GREEN)"
	@for i in $(shell seq 1 25); do \
		if [ $$i -le $$(($(COMPILED_SRCS)*25/$(TOTAL_SRCS))) ]; then \
			echo -n "♥"; \
		else \
			echo -n "."; \
		fi; \
	done
	@echo -n "$(COLOR_RESET)] $(COMPILED_SRCS)/$(TOTAL_SRCS)\r"
	
	
#create the lib with the objects
$(NAME): $(OBJ_DIR) $(OBJ)
	@echo "$(COLOR_BLUE)\nCompiling Libft...$(COLOR_RESET)"
	@make -s -C ft_printf
	@cp $(FT_PRINTF) .
	@mv libftprintf.a $(NAME)
	@ar rcs $(NAME) $(OBJ)
	@echo "$(COLOR_GREEN)Libft complete !$(COLOR_RESET)        "

#cleaning the objects files
clean:
	@rm -rf $(OBJ_DIR)
	@make -s -C ft_printf clean

#first do clean then rm the lib
fclean: clean
	@echo "$(COLOR_BLUE)✘✘✘ Deleting Libft... ✘✘✘$(COLOR_RESET)"
	@rm -f $(NAME)
	@make -s -C ft_printf fclean
	@echo "$(COLOR_GREEN)✘✘✘ Libft fcleaned ! ✘✘✘$(COLOR_RESET)        "

re: fclean all
