/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhalo <aelkhalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:10:39 by aelkhalo          #+#    #+#             */
/*   Updated: 2022/02/18 04:28:45 by aelkhalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_env()
{
    t_env *tmp;

    tmp = g_all.env;
    while (tmp != NULL)
    {
        if (tmp->value)
            printf("%s=%s\n", tmp->key,tmp->value);
        tmp = tmp->next;
    }
}