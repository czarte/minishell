NAME = minishell

SRC = main.c src/data.c src/exec_folders.c src/get_cmd_path.c \
	src/builtin_cd.c src/cli.c src/lexer.c src/string_utils.c \
	src/lexer_token_type.c src/lexer_analyzer.c src/executor.c \
	src/builtin_echo.c src/builtin_env.c src/builtin_export_utils.c \
	src/builtin_export.c src/builtin_unset.c src/help.c

TSRC = src/data.c src/exec_folders.c src/get_cmd_path.c \
	src/builtin_cd.c src/cli.c src/lexer.c src/string_utils.c \
	src/lexer_token_type.c src/lexer_analyzer.c src/executor.c \
	src/builtin_echo.c src/builtin_env.c src/builtin_export_utils.c \
	src/builtin_export.c src/builtin_unset.c src/help.c

CC = clang
# -g flag changed to -gdwarf-4 because clang uses dwarf5 by default which is not
# compatible with valgrind 3.18.1
FLAGS = -Wall -Wextra -Werror -gdwarf-4 #-fsanitize=address #-static-libsan
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