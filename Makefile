NAME = minishell

LIBFT = -L./LIBFT -lft

CC = cc
# jenleve werror pour linstant pcq il casase les couilles
CFLAGS = -Wall -Wextra -g3 

SRC_DIR = src
OBJ_DIR = obj

SRC = \
	free.c \
	display_prompt.c \
	main.c

OBJ = $(addprefix $(OBJ_DIR)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))

.PHONY: all clean fclean re

# je suis dsl je sais pas comment on include le header
# jai mis manuellement pour linstant si tu peux maider XD stp
all: $(NAME)

# c pour faire un dossier plus propre en triant les obj
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
