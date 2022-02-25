/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelkhalo <aelkhalo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 02:40:13 by aelkhalo          #+#    #+#             */
/*   Updated: 2022/02/23 16:42:29 by aelkhalo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void     ft_pwd()
{
    char *buff;

    buff = getcwd(NULL, 0);
    if (buff)
    {
        printf("%s\n", buff);
        free(buff);
    }
    else
		printf("minishell:error retrieving current directory: getcwd failed\n");
}