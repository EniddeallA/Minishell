/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 00:56:44 by aelkhalo          #+#    #+#             */
/*   Updated: 2022/02/25 03:07:32 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env2(char **args)
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

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

char	*ft_strchr(const char *s, int c)
{
	int			i;
	int			j;
	int			r;
	const char	*s1;

	i = 0;
	j = -1;
	s1 = s;
	r = ft_strlen((char *)s1);
	while (i <= r)
	{
		if (s[i] == c)
		{
			j = i;
			break ;
		}
		i++;
	}
	if (j == -1)
		return (NULL);
	else
		return ((char *)(s + j));
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

void	ft_export(char **args)
{
	int		i;
	char	**tmp;

	if (n_args(args) == 1)
		ft_env2(args);
	else if (n_args(args) > 1)
	{
		i = 1;
		while (args[i])
		{
			tmp = ft_split(args[i], '=');
			if (!ft_isalpha(tmp[0][0]) && tmp[0][0] != '_')
				printf("minishell: export: `%s': not a valid identifier\n",
					args[i]);
			else if (ft_strchr(args[i], '='))
				add_replace(tmp);
			else if (!key_exist(tmp[0]))
				add_envv(tmp[0], NULL);
			i++;
		}
	}
}