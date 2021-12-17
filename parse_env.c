/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:08:15 by akhalid           #+#    #+#             */
/*   Updated: 2021/12/17 18:40:26 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_key(char *envv, int i)
{
	char *key;
	int j;

	key = (char *)malloc(sizeof(char) * i);
	j = 0;
	while (j < i)
	{
		key[j] = envv[j];
		j++;
	}
	key[j] = '\0';
	return (key);
}

char *get_value(char *envv, int i)
{
	char *value;
	int j;

	value = (char *)malloc(sizeof(char) * (ft_strlen(envv) - i + 1));
	j = 0;
	while (envv[i])
	{
		value[j] = envv[i];
		j++;
		i++;
	}
	value[j] = '\0';
	return (value);
}

t_env split_env(char *envv, char c)
{
	int i;
	t_env env;

	i = 0;
	while (envv[i] && envv[i] != c)
		i++;
	env.key = get_key(envv, i);
	env.value = get_value(envv, ++i);
	return (env);
}

void init_cmd(t_env *env)
{
	env->key = NULL;
	env->value = NULL;
}

void	parse_envv(t_command **cmd, char **envv)
{
	int i;
	
	i = 0;
	while (envv[i])
		i++;
	(*cmd)->env = (t_env *)malloc(sizeof(t_env) * (2048 + 1));
	init_cmd((*cmd)->env);
	i = 0;
	while (envv[i])
	{
		(*cmd)->env[i] = split_env(envv[i], '=');
		i++;
	}
	(*cmd)->n_env = i;
}
