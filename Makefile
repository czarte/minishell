NAME = minishell

SRC = src/main.c src/data.c src/exec_folders.c src/get_cmd_path.c \
	src/builtin_cd.c src/cli.c

CC = cc
FLAGS = -Wall -Wextra -Werror -g# -fsanitize=address #-static-libsan
LIB = -lreadline

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $@"
	@$(CC) $(OBJ) $(FLAGS) $(LIB) -o $(NAME)
	@echo "Done!"

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(FLAGS) $(LIB) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
