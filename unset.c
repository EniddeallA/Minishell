/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhalo <aelkhalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/18 08:51:25 by aelkhalo          #+#    #+#             */
/*   Updated: 2022/02/23 20:42:46 by aelkhalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else
		return (0);
}

void    ft_unset(char **args)
{
    int i;
    
    if (n_args(args) > 1)
    {
        i = 1;
        while (args[i])
        {
            if (!ft_isalpha(args[i][0]))
                printf("minishell: unset: `%s': not a valid identifier\n", args[i]);
            else
                delete_envv(args[i]);
            i++;
        }
    }
}