# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 14:24:17 by akhalid           #+#    #+#              #
#    Updated: 2022/02/25 01:53:39 by akhalid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAG		=	 -g3 -fsanitize=address
LRL			=	"-lreadline"
LDFLAGS		=	"-L/Users/akhalid/homebrew/Cellar/readline/8.1.1/lib"
CPPFLAGS	=	"-I/Users/akhalid/homebrew/Cellar/readline/8.1.1/include"

# LDFLAGS		=	"-L/goinfre/aelkhalo/.brew/Cellar/readline/8.1.2/lib"
# CPPFLAGS	=	"-I/goinfre/aelkhalo/.brew/Cellar/readline/8.1.2/include"

# LDFLAGS  = "-L/usr/local/lib"
# CPPFLAGS	=	"-I/usr/local/include"
SRC_MAIN		=	*.c


SRCS		=	$(SRC_MAIN)

all: $(NAME)

$(NAME): $(SRCS)
	@gcc $(CFLAG) $(SRCS) $(LDFLAGS) $(CPPFLAGS)  $(LRL) -o $(NAME) -g
	
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME) *.out

re: fclean all

