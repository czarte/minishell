NAME = minishell

SRC = main.c src/data.c src/parser/exec_folders.c src/parser/get_cmd_path.c \
	src/builtins/builtin_cd.c src/cli/cli.c src/lexer/lexer.c src/utils/string_utils.c \
	src/lexer/lexer_token_type.c src/lexer/lexer_analyzer.c src/executor/executor.c \
	src/builtins/builtin_echo.c src/builtins/builtin_env.c src/builtins/builtin_export_utils.c \
	src/builtins/builtin_export.c src/builtins/builtin_unset.c src/help.c src/executor/ft_executor.c \
	src/utils/executor_helpers.c src/executor/ft_pipes.c src/utils/free_utils.c \
	src/utils/libft_utils.c src/utils/list_utils.c src/utils/libft_memutils.c

TSRC = src/data.c src/parser/exec_folders.c src/parser/get_cmd_path.c \
	src/builtins/builtin_cd.c src/cli/cli.c src/lexer/lexer.c src/utils/string_utils.c \
	src/lexer/lexer_token_type.c src/lexer/lexer_analyzer.c src/executor/executor.c \
	src/builtins/builtin_echo.c src/builtins/builtin_env.c src/builtins/builtin_export_utils.c \
	src/builtins/builtin_export.c src/builtins/builtin_unset.c src/help.c

CC = clang
# -g flag changed to -gdwarf-4 because clang uses dwarf5 by default which is not
# compatible with valgrind 3.18.1
FLAGS = -Wall -Wextra -Werror -gdwarf-4 #-fsanitize=address -static-libsan
LIB = -lreadline

OBJ = $(SRC:.c=.o)
TOBJS = $(SRC:.c=.o)

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

unittests: $(TOBJS)
	@echo "Creating Testing progam"
	@echo "."
	@echo ".."
	@echo "..."
	@echo ".o for tests was created"
	@c++ ./tests/unit_tests.cc -Iinclude -Igoogletest/googletest/include/ -std=c++14 -c -o unit_tests.o
	@c++ ./tests/main.cpp -Iinclude -Igoogletest/googletest/include/ -std=c++14 -c
	@c++ ./main.o ./unit_tests.o $(TOBJS) -I./incl ./googletest/build/lib/libgtest.a -o unit_test
	@echo "...."
	@echo "....."
	@echo "Done!"