/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhalid <akhalid@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:51:25 by aelkhalo          #+#    #+#             */
/*   Updated: 2022/02/27 22:56:16 by akhalid          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **args)
{
	int	i;

	if (n_args(args) > 1)
	{
		i = 1;
		while (args[i])
		{
			if (!ft_isalpha(args[i][0]))
				printf("minishell: unset: `%s': not a valid identifier\n",
					args[i]);
			else
				delete_envv(args[i]);
			i++;
		}
	}
}
