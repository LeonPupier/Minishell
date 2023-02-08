# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vcart <vcart@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 08:32:06 by lpupier           #+#    #+#              #
#    Updated: 2023/02/08 20:28:00 by vcart            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Constants
NAME		=	minishell
CFLAGS		=	-Wall -Wextra -Werror

# Directories path
DIR_SRCS	=	sources/
DIR_HEADERS	=	includes/
DIR_LIBFT	=	libft/
DIR_PIPEX	=	pipex/
LIBFT		=	$(DIR_LIBFT)libft.a
PIPEX		=	$(DIR_PIPEX)pipex

# Files path
HEADERS	=	$(DIR_HEADERS)

SRCS	=	$(DIR_SRCS)main.c \
			$(DIR_SRCS)utils.c \
			$(DIR_SRCS)signals.c \
			$(DIR_SRCS)verify_args.c \
			$(DIR_SRCS)ft_echo.c \
			$(DIR_SRCS)ft_pwd.c \
			$(DIR_SRCS)ft_env.c \
			$(DIR_SRCS)ft_export.c \
			$(DIR_SRCS)list_utils.c \
			$(DIR_SRCS)ft_unset.c \
			$(DIR_SRCS)ft_check_export.c \
			$(DIR_SRCS)ft_cd.c \
			$(DIR_SRCS)ft_tab.c

OBJS	=	$(SRCS:.c=.o)

# Rules
.PHONY :	all re clean fclean FORCE watermark

all :	 	$(NAME)

%.o: %.c	$(HEADERS) Makefile
			$(CC) $(CFLAGS) -c $< -o $@ -I ${HEADERS}

${NAME}:	$(LIBFT) $(PIPEX) $(OBJS)
			$(CC) $(CFLAGS) $(OBJS) -lreadline $(DIR_LIBFT)libft.a -o $(NAME)

$(LIBFT):	FORCE
			$(MAKE) -C $(DIR_LIBFT)

$(PIPEX):	FORCE
			$(MAKE) -C $(DIR_PIPEX)

clean:
			$(RM) $(OBJS)
			$(MAKE) clean -C $(DIR_LIBFT)
			$(MAKE) clean -C $(DIR_PIPEX)

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) fclean -C $(DIR_LIBFT)
			$(MAKE) fclean -C $(DIR_PIPEX)

re :		fclean all

watermark:
			@echo "$$WATERMARK"

FORCE:

# Text art
define WATERMARK

\x1b[34;36m██╗  ██╗██████╗ \x1b[0m
\x1b[34;36m██║  ██║╚════██╗\x1b[0m name:  Leon Pupier • Valentin Cart
\x1b[34;36m███████║ █████╔╝\x1b[0m login: lpupier	    • vcart
\x1b[34;36m╚════██║██╔═══╝ \x1b[0m 
\x1b[34;36m     ██║███████╗\x1b[0m
\x1b[34;36m     ╚═╝╚══════╝lyon.fr\x1b[0m

endef
export WATERMARK