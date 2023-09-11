NAME = minishell

SRC = \
main.c \
parser/utils.c \
parser/utils_lists.c \
parser/utils_parser.c \
parser/lexer.c \
parser/syntax_check_1.c \
parser/expander.c \
env_parse/envcpy.c \
env_parse/env_utils.c \


OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror

CC = gcc

LIBFT_DIR = libft

LIBFT_A = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT_A) $(OBJ)
	$(CC) -lreadline $(CFLAGS) -I $(LIBFT_DIR) $(LIBFT_A) $(OBJ) -o $(NAME)

$(LIBFT_A):
	make -C libft

%.o: %.c
	$(CC) $(CFLAGS) -I $(LIBFT_DIR) -c -o $@ $^

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(NAME) libft/libft.a

re: fclean all

.PHONY: all clean fclean re