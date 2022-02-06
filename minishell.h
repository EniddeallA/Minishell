/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:01 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/06 02:33:36 by akhalid          ###   ########.fr       */
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
	int lexer_err;
	int exit_status;
}	t_all;

t_all g_all;

typedef struct s_lexer
{
	char *cmd;
	int i;
	char c;
	int length;
}	t_lexer;

typedef enum s_type
{
	WRD,
	PIPE,
	INP,
	OUT,
	APND,
	HRDOC
}	t_type;

typedef struct s_token
{
	char *val;
	t_type type;
}	t_token;

/*
	collect_env.c
*/

void collect_env(char **envv);

/*
	parser.c
*/

void parser();
t_token *get_token(t_lexer *lexer);

/*
	lexer.c
*/

t_lexer	*init_lexer();
void	lexer_forward(t_lexer *lexer);
void	lexer_backward(t_lexer *lexer);
char *lexer_to_string(t_lexer *lexer);

/*
	token.c
*/

t_token *init_token(t_type type, char *val);
t_token *token_lf(t_lexer *lexer, t_token *token);
t_token *operator_token(t_lexer *lexer);
t_token *quoted_wrd_token(t_lexer *lexer, char c);
t_token *unquoted_wrd_token(t_lexer *lexer);

/*
	char_token.c
*/

char *more_wrd_token(t_lexer *lexer, char *val);
char *char_quoted_wrd_token(t_lexer *lexer, char c);
char *char_unquoted_wrd_token(t_lexer *lexer);

/*
	expand.c
*/

char *expand_exit_status(t_lexer *lexer);
char *more_expansion(t_lexer *lexer, char *tmp);
char *unquoted_expansion(t_lexer *lexer);
char *quoted_expansion(t_lexer *lexer);

/*
	utils.c
*/

int	ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
int ft_isspace(char c);
void	skip_spaces(t_lexer *lexer);
int is_operator(char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
int check_line();

#endif