# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lpupier <lpupier@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/02 08:32:06 by lpupier           #+#    #+#              #
#    Updated: 2023/01/18 16:56:53 by lpupier          ###   ########.fr        #
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
HEADERS	=	$(DIR_HEADERS)minishell.h

SRCS	=	$(DIR_SRCS)main.c

OBJS	=	$(SRCS:.c=.o)

# Rules
.PHONY :	all re clean fclean FORCE watermark

all :	 	$(NAME)

%.o: %.c	$(HEADERS) Makefile
			$(CC) $(CFLAGS) -c $< -o $@

${NAME}:	$(LIBFT) $(PIPEX) $(OBJS)
			$(CC) $(CFLAGS) -lreadline $(OBJS) $(DIR_LIBFT)libft.a -o $(NAME)

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

██╗  ██╗██████╗ 
██║  ██║╚════██╗ name:  Leon Pupier • Valentin Cart
███████║ █████╔╝ login: lpupier	    • vcart
╚════██║██╔═══╝  
     ██║███████╗
     ╚═╝╚══════╝lyon.fr

endef
export WATERMARK