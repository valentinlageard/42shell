LIBFT		=	libft/libft.a
NAME		=	minishell
SRC			=	src/minishell.c \
				src/parse/parse.c \
				src/parse/expand_vars.c \
				src/parse/cltok.c \
				src/parse/tok_to_cmdg.c \
				src/parse/tok.c \
				src/parse/tok_utils.c \
				src/parse/tokenize.c \
				src/parse/tokenize2.c \
				src/exec/exec.c \
				src/exec/exec_cmd.c \
				src/exec/exec_utils.c \
				src/exec/fd_utils.c \
				src/exec/fd_utils2.c \
				src/exec/lpid.c \
				src/builtins/env_builtins.c \
				src/builtins/is_builtin.c \
				src/builtins/other_builtins.c \
				src/builtins/path_builtins.c \
				src/utils/binpath.c \
				src/utils/cmd.c \
				src/utils/cmdg.c \
				src/utils/env.c \
				src/utils/error_exit.c \
				src/utils/init.c \
				src/utils/inr.c \
				src/utils/outr.c \
				src/utils/signal_handling.c \
				src/utils/read_line.c \
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
