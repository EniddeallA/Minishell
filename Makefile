# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eniddealla <eniddealla@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 14:24:17 by akhalid           #+#    #+#              #
#    Updated: 2021/12/31 04:17:13 by eniddealla       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror -g
LRL			=	"-lreadline"
# LDFLAGS		=	"-L/Users/akhalid/homebrew/Cellar/readline/8.1.1/lib"
# CPPFLAGS	=	"-I/Users/akhalid/homebrew/Cellar/readline/8.1.1/include"
LDFLAGS  = "-L/usr/local/lib"
CPPFLAGS	=	"-I/usr/local/include"
SRC_MAIN		=	main.c \


SRCS		=	$(SRC_MAIN)

all: $(NAME)

$(NAME): $(SRCS)
	@gcc $(SRCS) $(LDFLAGS) $(CPPFLAGS)  $(LRL) -o $(NAME) -g
	
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME) *.out

re: fclean all