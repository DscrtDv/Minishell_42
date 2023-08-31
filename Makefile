NAME = minishell

SRC = \
src/main.c \
src/exec/exec.c \
src/utils/utils.c \
src/built-ins/echo.c \
src/built-ins/pwd.c \


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