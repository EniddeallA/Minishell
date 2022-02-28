/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collect_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 15:04:58 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/28 01:51:14 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

char	*add_key(char *str)
{
	int		i;
	char	*key;
	int		length;

	length = 0;
	while (str[length] && str[length] != '=')
		length++;
	i = 0;
	key = (char *)malloc(sizeof(char) * (length + 1));
	while (str[i] && str[i] != '=')
	{
		key[i] = str[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*add_value(char *str)
{
	int		i;
	char	*value;
	int		index;
	int		length;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			index = i + 1;
		i++;
	}
	length = i - index;
	value = (char *)malloc(sizeof(char) * (length + 1));
	i = 0;
	while (str[index])
		value[i++] = str[index++];
	value[i] = '\0';
	return (value);
}

t_env	*create_node(char *envv)
{
	t_env	*node;

	node = (t_env *)malloc(sizeof(t_env));
	node->key = add_key(envv);
	node->value = add_value(envv);
	node->next = NULL;
	return (node);
}

void	collect_env(char **envv)
{
	int		i;
	t_env	*head;
	t_env	*last;
	t_env	*new;

	head = NULL;
	i = 0;
	while (envv[i])
	{
		last = head;
		new = create_node(envv[i]);
		if (!head)
			head = new;
		else
		{
			while (last->next)
				last = last->next;
			last->next = new;
		}
		free_env(new);
		i++;
	}
	g_all.env = head;
	g_all.env_arr = env_to_arr();
}
