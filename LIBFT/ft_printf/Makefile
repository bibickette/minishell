# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phwang <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/29 14:42:47 by phwang            #+#    #+#              #
#    Updated: 2024/09/21 13:38:02 by phwang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME of my prog
NAME = libftprintf.a

OBJ_DIR = obj
SRC_DIR = src

#SRC FILES AND OBJECTS FILES, SRC with the command : find . -name "ft_*.c"
SRC = \
	ft_printf.c\
	ft_putnbr_fts.c\
	ft_small.c

OBJ =  $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

#PROGRESS BAR
TOTAL_SRCS := $(words $(SRC))
COMPILED_SRCS := 0
#COLOR SET
COLOR_RESET = \e[0m
COLOR_GREEN = \e[36m
COLOR_BLUE = \e[36m

#COMPILER & FLAGS
CC = cc
CFLAGS = -Wall -Wextra -Werror -g3

#Not a file
.PHONY: all clean fclean re bonus

#make start here
#compile the NAME then clean the OBJ
all: $(NAME)
	
$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

#compile les .c de src vers /obj
$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<
	
	@$(eval COMPILED_SRCS=$(shell echo $$(($(COMPILED_SRCS)+1))))
	@echo -n "$(COLOR_BLUE)Compiling Objects Printf: $(COLOR_RESET)[$(COLOR_GREEN)"
	@for i in $(shell seq 1 25); do \
		if [ $$i -le $$(($(COMPILED_SRCS)*25/$(TOTAL_SRCS))) ]; then \
			echo -n "♠"; \
		else \
			echo -n "."; \
		fi; \
	done
	@echo -n "$(COLOR_RESET)] $(COMPILED_SRCS)/$(TOTAL_SRCS)\r"
	
#create the lib with the objects
$(NAME): $(OBJ_DIR) $(OBJ)
	@echo "$(COLOR_BLUE)\nCompiling Printf...$(COLOR_RESET)"
	@ar rcs $(NAME) $(OBJ)
	@echo "$(COLOR_GREEN)Printf complete !$(COLOR_RESET)        "
#cleaning the objects files
clean:
	@rm -rf $(OBJ_DIR) 

#first do clean then rm the lib
fclean: clean
	@echo "$(COLOR_BLUE)✘✘✘ Deleting Printf... ✘✘✘$(COLOR_RESET)"
	@rm -f $(NAME)
	@echo "$(COLOR_GREEN)✘✘✘ Printf fcleaned ! ✘✘✘$(COLOR_RESET)        "

re: fclean all
