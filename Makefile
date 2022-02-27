# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 14:24:17 by akhalid           #+#    #+#              #
#    Updated: 2022/02/27 15:48:30 by akhalid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAG		=	 -g3 -fsanitize=address -g
LRL			=	"-lreadline"
LDFLAGS		=	"-L/Users/akhalid/homebrew/Cellar/readline/8.1.1/lib"
CPPFLAGS	=	"-I/Users/akhalid/homebrew/Cellar/readline/8.1.1/include"

# LDFLAGS		=	"-L/goinfre/aelkhalo/.brew/Cellar/readline/8.1.2/lib"
# CPPFLAGS	=	"-I/goinfre/aelkhalo/.brew/Cellar/readline/8.1.2/include"

# LDFLAGS  = "-L/usr/local/lib"
# CPPFLAGS	=	"-I/usr/local/include"
SRC_MAIN		=	cd.c collect_env.c env.c env_utils.c execute_cmd.c exit.c \
					expand_utils.c ft_itoa.c heredoc.c main.c parse_redirection.c \
					pwd.c token.c utils.c utils3.c char_token.c echo.c env_to_arr.c \
					execute.c execution_utils.c expand.c export.c ft_split.c lexer.c \
					parse_command.c parser.c redirection.c unset.c utils2.c


SRCS		=	$(SRC_MAIN)

all: $(NAME)

$(NAME): $(SRCS)
	@gcc $(CFLAG) $(SRCS) $(LDFLAGS) $(CPPFLAGS)  $(LRL) -o $(NAME) -g
	
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME) *.out

re: fclean all

