NAME = minishell

SRC = src/main.c src/data.c src/exec_folders.c src/get_cmd_path.c \
	src/builtin_cd.c src/cli.c src/lexer.c src/string_utils.c \
	src/lexer_token_type.c src/lexer_analyzer.c src/executer.c \
	src/builtin_echo.c src/builtin_env.c src/builtin_export_utils.c

CC = clang
FLAGS = -Wall -Wextra -Werror -gdwarf-4 #-fsanitize=address #-static-libsan
LIB = -lreadline

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $@"
	@$(CC) $(OBJ) $(FLAGS) $(LIB) -o $(NAME)
	@echo "Done!"

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
