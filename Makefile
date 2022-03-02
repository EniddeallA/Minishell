# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 14:24:17 by akhalid           #+#    #+#              #
#    Updated: 2022/03/02 20:52:52 by akhalid          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CC			=	gcc
CFLAG		=	-Werror -Wextra -Wall -g
LRL			=	"-lreadline"
LDFLAGS		=	"-L/Users/akhalid/homebrew/Cellar/readline/8.1.2/lib"
CPPFLAGS	=	"-I/Users/akhalid/homebrew/Cellar/readline/8.1.2/include"

# LDFLAGS		=	"-L/goinfre/aelkhalo/.brew/Cellar/readline/8.1.2/lib"
# CPPFLAGS	=	"-I/goinfre/aelkhalo/.brew/Cellar/readline/8.1.2/include"


SRC_MAIN	=	main.c collect_env.c env.c env_utils.c execute_cmd.c exit.c	\
				expand_utils.c ft_itoa.c heredoc.c parse_redirection.c		\
				pwd.c token.c char_token.c echo.c env_to_arr.c execute.c	\
				execution_utils.c expand.c export.c ft_split.c lexer.c		\
				parse_command.c parser.c redirection.c unset.c signals.c	\
				cd.c utils.c utils2.c utils3.c utils4.c utils5.c

SRCS		=	$(SRC_MAIN)

all: $(NAME)

$(NAME): $(SRCS)
	@gcc $(CFLAG) $(SRCS) $(LDFLAGS) $(CPPFLAGS)  $(LRL) -o $(NAME) -g
	
clean:
	@rm -rf *.o

fclean: clean
	@rm -rf $(NAME) *.out

re: fclean all

