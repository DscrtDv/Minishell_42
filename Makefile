NAME		=	minishell

	# libft Variables #
LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

SRCS		=	src/main.c src/exec/exec.c src/builtins/echo.c src/builtins/pwd.c src/utils/utils.c \
				src/cd/cd.c
OBJS		= 	$(SRCS:.c=.o)
INC			=	-I. -I$(LIBFT_DIR)
				
	# Compiling Variables #
CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror
RM			=	rm -f

	# Colors #
GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

	# Debugger #
ifeq ($(DEBUG), 1)
	D_FLAG	=	-g
endif

	# Fsanitize #
ifeq ($(SANITIZE), 1)
	D_FLAG	=	-fsanitize=leak -g
endif

all: $(NAME)

$(NAME): $(LIBFT)
	@ $(CC) -lreadline $(D_FLAG) $(CFLAG) $(SRCS) $(LIBFT) $(INC) -o $(NAME)
	@printf "$(_SUCCESS) $(NAME) ready.\n"

$(LIBFT):
	@ $(MAKE) DEBUG=$(DEBUG) -C $(LIBFT_DIR)

clean:
	@printf "$(_INFO) Cleaning $(NAME) object files.\n"
	@make -C libft clean
	@rm -f $(OBJS)
	@printf "$(_INFO) Object Files deleted.\n"

fclean: clean
	@ $(MAKE) fclean -C $(LIBFT_DIR)
	@ $(RM) $(NAME)
	@printf "$(_INFO) $(NAME) and libft.a removed.\n"

re: fclean all

mandatory:	$(NAME)
bonus:		mandatory

m : mandatory
b : bonus

.PHONY: all clean fclean re mandatory m bonus b