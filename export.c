/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 00:56:44 by aelkhalo          #+#    #+#             */
/*   Updated: 2022/03/02 02:30:04 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env2(void)
{
	t_env	*tmp;

	tmp = g_all.env;
	while (tmp != NULL)
	{
		if (tmp->value == NULL)
			printf("declare -x %s\n", tmp->key);
		else
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	g_all.exit_status = 0;
}

void	add_replace(char **tmp)
{
	if (!key_exist(tmp[0]))
	{
		if (tmp[1])
			add_envv(tmp[0], tmp[1]);
		else
			add_envv(tmp[0], "");
	}
	else if (tmp[0][0] == '_')
		;
	else
	{
		if (tmp[1])
			replace_value(tmp[0], tmp[1]);
		else
			replace_value(tmp[0], "");
	}
}

int	check_arg(char *tmp, char *identifier)
{
	int	i;

	if (!ft_isalpha(tmp[0]) && tmp[0] != '_')
	{
		printf("minishell: export: `%s': not a valid identifier\n",
			identifier);
		return (0);
	}
	i = 1;
	while (tmp[i])
	{
		if (!isalpha_num(tmp[i]) && tmp[i] != '_')
		{
			printf("minishell: export: `%s': not a valid identifier\n",
				identifier);
			return (0);
		}
		i++;
	}
	return (1);
}

static char	**split_env(char *str, char c)
{
	int		i;
	char	**env;
	int		size;

	size = 0;
	env = (char **)malloc(sizeof(char *) * 3);
	while (str[size] && str[size] != c)
		size++;
	env[0] = (char *)malloc(size + 1);
	ft_strlcpy(env[0], str, size + 1);
	size++;
	i = size;
	while (str[size])
		size++;
	env[1] = (char *)malloc(size - i);
	ft_strlcpy(env[1], &str[i], size - i + 1);
	env[2] = "\0";
	return (env);
}

void	ft_export(char **args)
{
	int		i;
	char	**tmp;

	g_all.exit_status = 1;
	if (n_args(args) == 1)
		ft_env2();
	else if (n_args(args) == 2)
	{
		i = 1;
		while (args[i])
		{
			tmp = split_env(args[i], '=');
			if (!check_arg(tmp[0], args[i]))
				return ;
			else if (ft_strchr(args[i], '='))
				add_replace(tmp);
			else if (!key_exist(tmp[0]))
				add_envv(tmp[0], NULL);
			i++;
		}
		g_all.exit_status = 0;
		free_tmp(tmp);
	}
	else
		printf("minishell: export: not a valid identifier\n");
}
