/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:01 by akhalid           #+#    #+#             */
/*   Updated: 2021/12/16 16:19:28 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>

# define IN_RED 1 // <
# define OUT_RED 2 // >
# define APPEND_RED 3 // >>
# define HERE_DOC 4 // <<

typedef struct s_redirect
{
	int type;
	char *value;
	struct s_redirect *next;
}   t_redirect;

typedef struct s_command
{
	char **args;
	t_redirect *in;
	t_redirect *out;
}   t_command;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}   t_env;


t_command   *parse_commands(char *line, t_env *env);
t_env *parse_envv(char **envv);
int ft_strlen(char *s);

#endif