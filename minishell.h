/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniddealla <eniddealla@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:01 by akhalid           #+#    #+#             */
/*   Updated: 2022/01/20 15:11:29 by eniddealla       ###   ########.fr       */
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
	t_redirect *inp;
	t_redirect *out;
	t_redirect *app;
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
char *ft_substr(char *s, unsigned int start, size_t len);
void skip_all_quotes(char *line, int *index);
int check_line(char *line);
int count_pipes(char *line);

#endif