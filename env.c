/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:10:39 by aelkhalo          #+#    #+#             */
/*   Updated: 2022/03/02 02:35:27 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(char **args)
{
	t_env	*tmp;

	if (n_args(args) == 1)
	{
		tmp = g_all.env;
		while (tmp != NULL)
		{
			if (tmp->value)
				printf("%s=%s\n", tmp->key, tmp->value);
			tmp = tmp->next;
		}
	}
	g_all.exit_status = 0;
}
