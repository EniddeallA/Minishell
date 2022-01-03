/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniddealla <eniddealla@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:01 by akhalid           #+#    #+#             */
/*   Updated: 2021/12/31 04:20:30 by eniddealla       ###   ########.fr       */
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
	char **command;
	t_redirect *in;
	t_redirect *out;
}   t_command;

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}   t_env;

typedef struct s_all
{
	int n_env;
	t_command *cmd;
	t_env *env;
}	t_all;

t_all g_all;


#endif