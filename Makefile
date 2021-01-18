LIBFT		=	libft/libft.a
NAME		=	minishell
SRC			=	src/minishell.c \
				src/repl/repl.c \
				src/repl/exec.c \
				src/parsing/expand_var.c \
				src/parsing/parse.c \
				src/parsing/token_utils.c \
				src/parsing/tokenizes.c \
				src/parsing/tokenizes2.c \
				src/parsing/tok_to_cmds.c \
				src/builtins/basic_builtins.c \
				src/builtins/path_builtins.c \
				src/builtins/builtin_utils.c \
				src/utils/error_exit.c \
				src/utils/init.c \
				src/utils/environ.c \
				src/utils/binpath.c \
				src/utils/cmd.c \
				src/utils/dir.c \
				src/utils/var.c

OBJS		=	$(SRC:.c=.o)

FLAGS		=	-Wall -Wextra # -Werror
CC			=	gcc $(FLAGS)

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT)
			$(CC) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c
			$(CC) -Iinclude -c $< -o $@

$(LIBFT):
			make -C libft

clean:
			rm -f $(OBJS)
			make -C libft clean

fclean:
			make clean
			rm -f $(NAME)
			rm -f $(LIBFT)

re:			fclean all

.PHONY: 	all clean fclean re
