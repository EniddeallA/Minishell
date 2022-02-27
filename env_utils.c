/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 03:32:01 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/27 15:30:24 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_value(char *key)
{
	t_env	*env;

	env = g_all.env;
	if (env)
	{
		while (env)
		{
			if (!ft_strcmp(env->key, key))
				return (env->value);
			env = env->next;
		}
	}
	return (0);
}

int	key_exist(char *key)
{
	t_env	*env;

	env = g_all.env;
	if (env)
	{
		while (env)
		{
			if (!ft_strcmp(env->key, key))
				return (1);
			env = env->next;
		}
	}
	return (0);
}

void	replace_value(char *key, char *new_value)
{
	t_env	*env;
	char	*temp;

	env = g_all.env;
	if (env)
	{
		while (env)
		{
			if (!ft_strcmp(env->key, key))
			{
				free(env->value);
				env->value = ft_strdup(new_value);
				break ;
			}
			env = env->next;
		}
	}
}

void	delete_envv(char *key)
{
	t_env	*env;
	t_env	*temp;

	env = g_all.env;
	if (env)
	{
		if (!ft_strcmp(env->key, key))
		{
			temp = env;
			g_all.env = env->next;
			free_env(temp);
		}
		else
		{
			while (env->next)
			{
				if (!compare_env(&env, key))
					break ;
				env = env->next;
			}
		}
	}
	free_env_arr();
	g_all.env_arr = env_to_arr();
}

void	add_envv(char *key, char *value)
{
	t_env	*env;
	t_env	*new_env;

	env = g_all.env;
	if (env)
		while (env->next != NULL)
			env = env->next;
	new_env = (t_env *)malloc(sizeof(t_env));
	new_env->key = ft_strdup(key);
	new_env->value = NULL;
	if (value)
		new_env->value = ft_strdup(value);
	new_env->next = NULL;
	env->next = new_env;
}
