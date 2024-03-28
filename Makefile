NAME = minishell

SRC = src/main.c src/data.c

CC = cc
FLAGS = -Wall -Wextra -Werror -g# -fsanitize=address #-static-libsan
PRINT_FLAG = -D PRINT_NUMBER_OF_EATS=1

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@echo "Linking $@"
	@$(CC) $(OBJ) $(FLAGS) -o $(NAME)
	@echo "Done!"

%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(FLAGS) $(PRINT_FLAG) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
