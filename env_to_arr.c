/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_to_arr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 03:18:14 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/25 02:51:26 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_arr(void)
{
	int	i;

	i = 0;
	while (g_all.env_arr[i])
		free(g_all.env_arr[i++]);
	free(g_all.env_arr[i]);
}

int	env_length(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	*get_env(t_env *env, int index)
{
	char	*str;
	int		i;

	i = 0;
	while (env->next && i < index)
	{
		env = env->next;
		i++;
	}
	if (env->value)
	{
		str = ft_strjoin(ft_strdup(env->key), ft_strdup("="));
		str = ft_strjoin(str, ft_strdup(env->value));
	}
	return (ft_strdup(str));
}

char	**env_to_arr(void)
{
	t_env	*env;
	int		size;
	char	**env_arr;
	int		i;

	env = g_all.env;
	size = env_length(env);
	env_arr = (char **)malloc(sizeof(char *) * (size + 2));
	if (!env_arr)
		return (0);
	i = 0;
	while (i < size)
	{
		env_arr[i] = get_env(env, i);
		i++;
	}
	env_arr[i] = 0;
	return (env_arr);
}
