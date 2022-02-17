/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:01 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/17 05:52:44 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>

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

void	collect_env(char **envv);

/*
	parser.c
*/

void	parse();
t_token *get_token(t_lexer *lexer);
t_token	**realloc_tokens(t_token **tokens, t_token *tmp);
void	free_tokens(t_token **tokens);
void parse_commands(t_token **tokens);
int syntax_error(t_token **token);


/*
	lexer.c
*/

t_lexer	*init_lexer();
void	lexer_forward(t_lexer *lexer);
void	lexer_backward(t_lexer *lexer);
char	*lexer_to_string(t_lexer *lexer);

/*
	token.c
*/

t_token	*init_token(t_type type, char *val);
t_token *token_lf(t_lexer *lexer, t_token *token);
t_token *operator_token(t_lexer *lexer);
t_token *quoted_wrd_token(t_lexer *lexer, char c);
t_token *unquoted_wrd_token(t_lexer *lexer);

/*
	char_token.c
*/

char	*more_wrd_token(t_lexer *lexer, char *val);
char	*char_quoted_wrd_token(t_lexer *lexer, char c);
char	*char_unquoted_wrd_token(t_lexer *lexer);

/*
	expand.c
*/

char *expand_exit_status(t_lexer *lexer);
char *more_expansion(t_lexer *lexer, char *tmp);
char *unquoted_expansion(t_lexer *lexer);
char *quoted_expansion(t_lexer *lexer);

/*
	expand.c
*/

char *expand_exit_status(t_lexer *lexer);
char *get_env_value(char *key);
char	*expand_key(char *key);
char *more_expansion(t_lexer *lexer, char *tmp);


/*
	parse_command.c
*/

void 	token_to_cmd(t_token **tokens, t_command *cmd, int i);
char **realloc_args(char **args, char *val);
t_command	*init_command();
void	free_args(char **args);

/*
	parse_redirection.c
*/

void 	create_redirection(t_redirect *red, char *val, t_type type);
t_redirect	*init_redirection(char *val, t_type type);

/*
	utils.c
*/

int		ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);
int 	ft_isspace(char c);
void	skip_spaces(t_lexer *lexer);
int 	is_operator(char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *s1);
int 	check_line();
int		ft_strcmp(char *s1, char *s2);
char	*ft_itoa(int n);
int		ft_strcmp(char *s1, char *s2);

typedef struct s_pipe
{
	int pid;
	int pipe[2];
	int inp;
	int outp;
	int state;
	int last_state;
	int last_pid;
}	t_pipe;

/*
	execute.c
*/

void	execute(t_command *cmd);
void	complex_cmd(t_command *cmd);
void	simple_cmd(t_command *cmd);
void	single_cmd(t_command *cmd, t_pipe *p);
void	multiple_cmds(t_command *cmd, t_pipe *p);
void	last_cmd(t_command *cmd, t_pipe *p);
void	execute_cmd(t_command *cmd);
void	redirect(t_command *cmd);
void	execute_builtins(t_command *cmd);

/*
	execution_utils.c
*/

void	cntl_c(int sig);
int		is_builtin(char *cmd);

/*
	env_utils.c
*/

void	add_envv(char *key, char *value);
void	delete_envv(char *key);
void	replace_value(char *key, char *new_value);
char	*get_value(char *key);

/*
	builtins
*/

void	ft_echo(char **args);
void	ft_env();
void	ft_pwd();
void	ft_exit(char **args);

#endif