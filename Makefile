LIBFT		=	libft/libft.a
NAME		=	minishell
SRC			=	src/minishell.c \
				src/repl/repl.c \
				src/repl/exec.c \
				src/utils/error.c \
				src/utils/init.c \
				src/utils/environ.c

OBJS		=	$(SRC:.c=.o)

FLAGS		=	#-Wall -Wextra -Werror
CC			=	gcc $(FLAGS)

all:		$(NAME)

$(NAME):	$(OBJS) $(LIBFT) -lm
			$(CC) $(OBJS) $(LIBFT) -o $(NAME) -lm

%.o: %.c
			$(CC) -Iinclude -c $< -o $@ -lm

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
