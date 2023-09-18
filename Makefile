NAME		=	minishell

	# libft Variables #
LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

SRCS		=	src/main.c \
				src/parser/expander.c \
				src/parser/lexer.c \
				src/utils/syntax_check_1.c \
				src/utils/utils_lists.c \
				src/utils/utils_parser.c \
				src/utils/utils.c \
				src/builtins/echo.c \
				src/builtins/cd.c \
				src/builtins/pwd.c \
				src/builtins/env.c \
				src/builtins/unset.c \
				src/builtins/export.c \
				src/utils/utils_exec.c \
				src/exec/exec.c \
				src/exec/child_process.c \
				src/exec/redirections.c \
				src/env_parse/envcpy.c \
				src/env_parse/env_utils.c \
				src/error/error_handler.c \
				src/error/free.c \
	

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

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(D_FLAG) $(CFLAG) $(OBJS) $(LIBFT) $(INC) -lreadline -o $(NAME)
	@printf "$(_SUCCESS) $(NAME) ready.\n"

$(LIBFT):
	@ $(MAKE) DEBUG=$(DEBUG) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAG) $(INC) -c -o $@ $^

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