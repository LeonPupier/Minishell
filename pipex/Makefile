
SRCS	= ./sources/main.c ./sources/utils.c

OBJS	= ${SRCS:.c=.o}

HEADERS = ./includes/pipex.h

NAME	= pipex

CFLAGS	= -Wall -Wextra -Werror

%.o: %.c 	${HEADERS}
			${CC} ${CFLAGS} -c $< -o $@ -I ${HEADERS}


${NAME}:	${OBJS}
			$(CC) ${CFLAGS} ${OBJS} ../libft/libft.a -o ${NAME}

all:		${NAME}

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re 