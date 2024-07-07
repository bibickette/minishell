NAME = minishell

LIBFT = -L./LIBFT -lft

CC = cc


INCLUDE = -I. -I./LIBFT
CFLAGS = $(INCLUDE) -Wall -Wextra -g3 

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c) $(wildcard $(SRC_DIR)/**/*.c)

OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

.PHONY: all clean fclean re


all: $(NAME)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $< 

$(NAME) : $(OBJ_DIR) $(OBJ)
	make -s -C LIBFT
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME) 


clean:
	@make -s -C LIBFT clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -s -C LIBFT fclean
	@rm -f $(NAME)

re: fclean all
