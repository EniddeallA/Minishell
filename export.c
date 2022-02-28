/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 00:56:44 by aelkhalo          #+#    #+#             */
/*   Updated: 2022/02/28 23:54:20 by akhalid          ###   ########.fr       */
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

int	check_arg(char *tmp)
{
	int	i;

	if (!ft_isalpha(tmp[0]) && tmp[0] != '_')
		return (0);
	i = 1;
	while (tmp[i])
	{
		if (!isalpha_num(tmp[i]) && tmp[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_export(char **args)
{
	int		i;
	char	**tmp;

	if (n_args(args) == 1)
		ft_env2();
	else if (n_args(args) > 1)
	{
		i = 1;
		while (args[i])
		{
			tmp = ft_split(args[i], '=');
			if (!check_arg(tmp[0]))
				printf("minishell: export: `%s': not a valid identifier\n",
					args[i]);
			else if (ft_strchr(args[i], '='))
			{
				add_replace(tmp);
			}
			else if (!key_exist(tmp[0]))
				add_envv(tmp[0], NULL);
			i++;
		}
		free_tmp(tmp);
	}
}
