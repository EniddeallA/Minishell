# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 14:24:17 by akhalid           #+#    #+#              #
#    Updated: 2021/12/20 00:13:00 by akhalid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror -g
LRL			=	"-lreadline"
LDFLAGS		=	"-L/Users/akhalid/homebrew/Cellar/readline/8.1.1/lib"
CPPFLAGS	=	"-I/Users/akhalid/homebrew/Cellar/readline/8.1.1/include"

SRC_MAIN		=	main.c \
					parse_env.c \
					parse_cmd.c \
					utils.c \


SRCS		=	$(SRC_MAIN)

all: $(NAME)

$(NAME): $(SRCS)
	@gcc $(LRL)  $(LDFLAGS) $(CPPFLAGS) $(SRCS) -o $(NAME) -g
	
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME) *.out

re: fclean all