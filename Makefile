# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 14:24:17 by akhalid           #+#    #+#              #
#    Updated: 2021/11/29 17:11:59 by akhalid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror
LRL			=	"-lreadline"
LDFLAGS		=	"-L/Users/akhalid/homebrew/Cellar/readline/8.1.1/lib"
CPPFLAGS	=	"-I/Users/akhalid/homebrew/Cellar/readline/8.1.1/include"

SRC_MAIN		=	main.c


SRCS		=	$(SRC_MAIN)

all: $(NAME)

$(NAME): $(SRCS)
	@gcc $(LRL) $(CFLAG) $(LDFLAGS) $(CPPFLAGS) $(SRCS) -o $(NAME)
	
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME) *.out

re: fclean all