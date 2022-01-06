/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:01 by akhalid           #+#    #+#             */
/*   Updated: 2022/01/06 01:22:53 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <string.h>

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
	t_redirect *append;
	t_redirect *heredoc;
	int n_arg;
}   t_command;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}   t_env;

typedef struct s_all
{
	int n_cmd;
	t_command *cmd;
	t_env *env;
}	t_all;

t_all g_all;

void collect_env(char **envv);
void parse_line(char *line);
int ft_strlen(char *s);
char	*ft_substr(char *s, unsigned int start, size_t len);

#endif