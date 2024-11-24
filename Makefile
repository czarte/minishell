NAME = minishell

SRC = main.c src/loop.c src/data_init.c src/parser/exec_folders.c src/parser/get_cmd_path.c \
	src/builtins/builtin_cd.c src/cli/cli.c src/lexer/lexer.c src/utils/string_utils.c \
	src/lexer/lexer_token_type.c src/lexer/lexer_analyzer.c src/executor/executor.c \
	src/builtins/builtin_echo.c src/builtins/builtin_env.c src/builtins/builtin_export_utils.c \
	src/builtins/builtin_export.c src/builtins/builtin_unset.c src/help.c src/executor/ft_executor.c \
	src/utils/executor_helpers.c src/executor/ft_pipes.c src/utils/free_utils.c \
	src/utils/libft_utils.c src/utils/list_utils.c src/utils/libft_memutils.c src/utils/token_utils.c \
	src/signals/signals.c src/builtins/builtin_export_envp_utils.c src/utils/string_utils_1.c \
	src/lexer/lexer_fill_token_chain.c src/utils/lexer_token_type_utils.c src/utils/lexer_analyzer_utils.c \
	src/utils/lexer_analyzer_utils_1.c src/utils/exec_folders_utils.c src/data_free.c src/data_free_1.c \
	src/data_init_1.c src/utils/file_utils.c src/utils/ft_itoa.c src/utils/lexer_analyzer_utils_2.c \
	src/utils/ft_atoi.c src/utils/debug_utils.c src/lexer/token_space.c src/lexer/token_counter.c \
	src/lexer/fill_helpers.c src/executor/execute_helpers.c src/parser/ft_command_parser.c \
	src/lexer/lexer_expander.c src/utils/lexer_expander_utils.c src/parser/count_utils.c \
	src/parser/get_array_utils.c src/parser/parser_garbage.c src/parser/skip_quote_split.c \
	src/utils/libft_utils_1.c src/utils/libft_utils_2.c src/utils/debug_utils_1.c \
	src/lexer/lexer_rm_unwanted_quotes.c src/lexer/lexer_quotes_pair_check.c \
	src/lexer/lexer_cmd_trim.c src/parser/get_array_helpers.c src/parser/cmd_path_helpers.c \
	src/builtins/builtin_exit.c

TSRC = loop.c src/data_init.c src/parser/exec_folders.c src/parser/get_cmd_path.c \
	src/builtins/builtin_cd.c src/cli/cli.c src/lexer/lexer.c src/utils/string_utils.c \
	src/lexer/lexer_token_type.c src/lexer/lexer_analyzer.c src/executor/executor.c \
	src/builtins/builtin_echo.c src/builtins/builtin_env.c src/builtins/builtin_export_utils.c \
	src/builtins/builtin_export.c src/builtins/builtin_unset.c src/help.c src/utils/token_utils.c \
	src/signals/signals.c src/builtins/builtin_export_envp_utils.c src/utils/string_utils_1.c \
	src/lexer/lexer_fill_token_chain.c src/utils/lexer_token_type_utils.c src/utils/lexer_analyzer_utils.c \
	src/utils/lexer_analyzer_utils_1.c src/utils/exec_folders_utils.c src/data_free.c src/data_free_1.c \
	src/data_init_1.c src/utils/file_utils.c src/utils/ft_itoa.c src/utils/lexer_analyzer_utils_2.c \
	src/loop.c src/utils/ft_atoi.c src/lexer/lexer_expander.c src/utils/lexer_expander_utils.c src/parser/count_utils.c \
	src/parser/get_array_utils.c src/parser/parser_garbage.c src/parser/skip_quote_split.c \
	src/parser/get_array_helpers.c src/parser/cmd_path_helpers.c src/parser/get_array_utils.c src/parser/parser_garbage.c \
	src/parser/skip_quote_split.c src/utils/libft_utils_1.c src/utils/libft_utils_2.c src/utils/debug_utils_1.c \
	src/lexer/lexer_rm_unwanted_quotes.c src/lexer/lexer_quotes_pair_check.c src/lexer/lexer_cmd_trim.c \
	src/builtins/builtin_exit.c

CC = clang
# -g flag changed to -gdwarf-4 because clang uses dwarf5 by default which is not
# compatible with valgrind 3.18.1
FLAGS = -Wall -Wextra -Werror -gdwarf-4 -fsanitize=address -static-libsan
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
