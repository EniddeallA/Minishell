/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:01 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/05 22:55:08 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>

# define INPUT 1
# define OUTPUT 2
# define APPEND 3
# define HEREDOC 4

typedef struct s_redirect
{
	int type;
	char *file;
	int index;
	int fd;
	struct s_redirect *next;
}   t_redirect;

typedef struct s_command
{
	char *cmd;
	int n_arg;
	char **args;
	t_redirect *red;
	struct s_command *next;
}   t_command;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}   t_env;

typedef struct s_all
{
	char *line;
	t_env *env;
	int n_cmd;
	t_command *cmd;
}	t_all;

t_all g_all;

typedef struct s_lexer
{
	char *content;
	int i;
	char c;
}	t_lexer;

typedef enum s_type
{
	WRD,
	PIPE,
	IN,
	OUT,
	APND,
	HRDOC
}	t_type;

typedef struct s_token
{
	char *val;
	t_type type;
}	t_token;

void parse_line();


void collect_env(char **envv);


int ft_strlen(char *s);
char *ft_substr(char *s, unsigned int start, size_t len);
int check_line();

#endif