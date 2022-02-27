/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:08:52 by akhalid           #+#    #+#             */
/*   Updated: 2022/02/27 15:31:01 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == '\t' || c == '\n'
		|| c == '\v' || c == '\f' || c == '\r'
		|| c == ' ');
}

int	is_operator(char c)
{
	return (c == '|' || c == '>' || c == '<');
}

int	is_all_spaces(char *s)
{
	int	i;

	i = 0;
	while (ft_isspace(s[i]) && s[i])
		i++;
	if (!s[i])
		return (1);
	return (0);
}

int	n_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	compare_env(t_env **env, char *key)
{
	t_env	*temp;

	if (!ft_strcmp((*env)->next->key, key))
	{
		temp = (*env)->next;
		(*env)->next = (*env)->next->next;
		free_env(temp);
		return (0);
	}
	return (1);
}
