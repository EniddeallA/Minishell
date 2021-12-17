/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:01 by akhalid           #+#    #+#             */
/*   Updated: 2021/12/17 18:44:03 by akhalid          ###   ########.fr       */
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

typedef struct s_env
{
	char *key;
	char *value;
}   t_env;

typedef struct s_command
{
	char **args;
	t_redirect *in;
	t_redirect *out;
	int n_env;
	t_env *env;
	int n_cmd;
}   t_command;

void	parse_commands(t_command **cmd, char *line);
void	parse_envv(t_command **cmd, char **envv);
int		ft_strlen(char *s);

#endif