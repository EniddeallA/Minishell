/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 13:08:01 by akhalid           #+#    #+#             */
/*   Updated: 2021/12/20 00:33:56 by akhalid          ###   ########.fr       */
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

typedef struct s_env
{
	char *key;
	char *value;
	struct s_env *next;
}   t_env;

typedef struct s_command
{
	char **args;
	t_redirect *in;
	t_redirect *out;
	t_env *env;
	int n_cmd;
}   t_command;



#endif