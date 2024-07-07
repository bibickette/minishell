NAME = minishell

LIBFT = -L./LIBFT -lft

CC = cc


INCLUDE = -I. -I./LIBFT
CFLAGS = $(INCLUDE) -Wall -Wextra -g3 

SRC_DIR = src
OBJ_DIR = obj

SRC = $(wildcard $(SRC_DIR)/*.c)

OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))


.PHONY: all clean fclean re


all: $(NAME)


$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
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
