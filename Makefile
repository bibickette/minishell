NAME = minishell

$(NAME) : $(addprefix src/, $(wildcard *.c))
	cc -o $(NAME) $(addprefix sources/, *.c) -include ./minishell.h

all: $(NAME)

clean:
	rm -f $(NAME)

fclean: clean

re: clean all
